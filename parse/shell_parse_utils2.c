/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:34:06 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/18 06:41:06 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../shell/shell.h"
#include "../parse/shell_parse_utils1.h"
#include "../libft/libft.h"

// parse_node에 담아둔 것은 정확한 크기를 모르고 malloc 한 거라
// list에 넣은 때는 정확한 크기 만큼 다시 malloc 함
// list의 tail이 NULL인 경우도 고려해서 이어 붙임
t_parse_node	*shell_parse_util_append_node_list(t_parse_node **node,
						t_parse_list *list)
{
	t_parse_node	*tmp;
	char			*ret;

	tmp = malloc(sizeof(t_parse_node));
	if (NULL == tmp)
		return (NULL);
	tmp->size = (*node)->cnt;
	tmp->cnt = (*node)->cnt;
	ret = shell_parse_util_node_to_str(node);
	if (NULL == ret)
	{
		free(tmp);
		return (NULL);
	}
	tmp->str = ret;
	if (list->tail)
		list->tail->next = tmp;
	list->tail = tmp;
	*node = shell_parse_util_new_node();
	if (NULL == *node)
		return (NULL);
	return (*node);
}

void	shell_parse_util_free_node(t_parse_node **node)
{
	if ((*node)->str)
		free((*node)->str);
	free((*node));
	*node = NULL;
}

void	shell_parse_util_free_list(t_parse_list *list)
{
	t_parse_node	*tmp;

	tmp = list->head.next;
	while (tmp)
	{
		list->head.next = tmp->next;
		shell_parse_util_free_node(&tmp);
		tmp = list->head.next;
	}
	return (0);
}

int	shell_parse_util_free_argv(char **argv, int cnt)
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
	return (-1); // 에러나는 상황에서만 이전 것 free하기 때문에 항상 -1인 S_P_ERROR를 리턴
}
