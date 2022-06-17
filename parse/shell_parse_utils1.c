/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:34:06 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/18 06:39:36 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../parse/shell_parse_utils1.h"
#include "../libft/libft.h"

t_parse_node *shell_parse_util_new_node()
{
	t_parse_node	*ret;

	ret = malloc(sizeof(t_parse_node));
	if (NULL == ret)
		return (NULL);
	ret->str = malloc(sizeof(char) * SHELL_PARSE_NODE_SIZE);
	if (NULL == ret->str)
	{
		free(ret);
		return (NULL);
	}
	ret->size = SHELL_PARSE_NODE_SIZE;
	ret->cnt = 0;
	ret->next = NULL;
	return (ret);
}

// list head가 dummy임
void	shell_prase_util_init_list(t_parse_list *list)
{
	list->cnt = 0;
	list->head.size = 0;
	list->head.cnt = 0;
	list->head.str = NULL;
	list->head.next = NULL;
	list->tail = NULL;
}

int	shell_parse_util_add_char_node(t_parse_node *node, char c)
{
	char	*ret;

	if (node->cnt == node->size)
	{
		ret = malloc(sizeof(char) * (node->size + SHELL_PARSE_NODE_SIZE));
		if (NULL == ret)
			return (-1);
		node->size += SHELL_PARSE_NODE_SIZE;
		ft_memcopy(ret, node->str, node->size);
		free(node->str);
		node->str = ret;
	}
	node->str[node->cnt++] = c;
	return (0);
}

// parse_node에 담아둔 것은 정확한 크기를 모르고 malloc 한 거라
// str로 만들 때는 정확한 크기 만큼 다시 malloc 함
char	*shell_parse_util_node_to_str(t_parse_node **node)
{
	char	*ret;

	ret = malloc(sizeof(char) * (*node)->cnt + 1); // node->str만 cnt크기에 딱 맞춰서 새로 할당
	if (NULL == ret)
		return (NULL);
	ret[(*node)->cnt] = '\0';
	ft_memcopy(ret, (*node)->str, (*node)->cnt);
	free((*node)->str);
	free(*node);
	*node = NULL;
	return (ret);
}

char	**shell_parse_util_list_to_argv(t_parse_list *list)
{
	char			**argv;
	int				cnt;
	t_parse_node	*node;
	int				free_cnt;

	argv = malloc(sizeof(char *) * list->cnt + 1);
	if (NULL == argv)
		return (NULL);
	argv[list->cnt] = NULL;
	cnt = -1;
	while (++cnt < list->cnt)
	{
		node = list->head.next;
		argv[cnt] = node->str; // list에 있던 str 포인터 그대로 가져감
		list->head.next = node->next;
		free(node);
	}
	list->tail = NULL;
}
