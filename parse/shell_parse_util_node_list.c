/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_util_node_list.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:57:15 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/21 15:43:24 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "shell_parse_node_list.h"
#include "../libft/libft.h"
#include "shell_parse_util_node_list.h"
#include "../env/env_list_interface_01.h"
#include "../utils/error_msg_utils_01.h"

int	shell_parse_node_add_char(t_parse_node *node, char c)
{
	char	*ret;

	if (node->cnt == node->size)
	{
		ret = malloc(sizeof(char) * (node->size + SHELL_PARSE_NODE_SIZE)); // node 크기가 SHELL_PARSE_NODE_SIZE 만큼 더해지고, 마지막에 '\0' 저장 안 하기 때문에 strdup 못 씀
		if (NULL == ret)
			return (-1);
		node->size += SHELL_PARSE_NODE_SIZE;
		ft_memcpy(ret, node->str, node->size);
		free(node->str);
		node->str = ret;
	}
	node->str[node->cnt++] = c;
	return (0);
}

// 원래 node free
// node str에 마지막에 '\0' 저장 안 하기 때문에 strdup 못 씀
char	*shell_parse_node_to_str(t_parse_node *node)
{
	char	*ret;

	ret = malloc(sizeof(char) * node->cnt + 1);
	if (NULL == ret)
		return (NULL);
	ret[node->cnt] = '\0';
	ft_memcpy(ret, node->str, node->cnt);
	free(node->str);
	free(node);
	return (ret);
}

char	**shell_parse_list_to_argv(t_parse_list *list) // 원래 list free
{
	char			**argv;
	int				cnt;
	t_parse_node	*node;
	char			*arg;

	argv = malloc(sizeof(char *) * list->cnt + 1);
	if (NULL == argv)
		return (NULL);
	argv[list->cnt] = NULL;
	cnt = -1;
	node = list->head.next;
	while (++cnt < list->cnt)
	{
		list->head.next = node->next;
		arg = shell_parse_node_to_str(node); // 원래 node free
		if (NULL == arg)
			shell_parse_util_argv_free(argv, cnt);
		argv[cnt] = arg;
		node = list->head.next;
	}
	list->tail.pre = NULL;
	return (argv);
}

void	shell_parse_util_argv_free(char **argv, int cnt)
{
	int	i;

	if (-1 == cnt)
	{
		i = -1;
		while (argv[++i])
			free(argv[i]);
		free(argv);
	}
	else
	{
		i = -1;
		while (++i < cnt && argv[i])
			free(argv[i]);
		free(argv);
	}
}

int	shell_parse_find_str_in_env(t_shell_data *p_data)
{
	char		*key;
	t_env_node	*env_node;
	int			cnt;

	key = shell_parse_node_to_str(p_data->parse_env);
	if (NULL == key)
		return (-1);
	if (env_node_search(&p_data->env_list, key, &env_node) == 0)
	{
		ft_perror_param("env", key, 0);
		free(key);
		return (-1);
	}
	free(key);
	cnt = -1;
	while (env_node->value[++cnt])
		if (shell_parse_node_add_char(p_data->parse_tmp, env_node->value[cnt]))
			return (-1);
	return (0);
}
