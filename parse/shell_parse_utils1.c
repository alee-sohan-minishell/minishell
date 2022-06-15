/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:34:06 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/12 11:09:20 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../parse/shell_parse_state.h"
#include "../parse/shell_parse_utils1.h"
#include "../libft/libft.h"

t_state_shell_parse	shell_parse_util_get_state(char c)
{
	int			cnt;
	const char	str[] = {' ', '\'', '"', '$', '#', '-', '~',
		'(', ')', '&', '|', '<', '>'};

	cnt = -1;
	while (++cnt < 13) // 13개 중에 매칭되는 상태 리턴
		if (str[cnt] == c)
			return (cnt);
	return (S_P_FINISH); // char c 만 제대로 넣으면 이거 리턴될 일 없음
}

void	shell_prase_util_init(t_parse_list *list)
{
	list->cnt = 0;
	list->head.cnt = 0;
	list->head.size = 0;
	list->head.str = NULL;
	list->head.next = NULL;
	list->tail = NULL;
}

// 새 node 만들어서 list tail에 이어 붙임, list의 tail이 NULL인 경우도 고려해서 이어 붙임
t_parse_node	*shell_parse_util_append_new_node(t_parse_list *list)
{
	t_parse_node	*node;

	node = malloc(sizeof(t_parse_node));
	if (NULL == node)
		return (NULL);
	node->str = malloc(sizeof(char) * SHELL_PARSE_NODE_SIZE);
	if (NULL == node->str)
	{
		free(node);
		return (NULL);
	}
	node->cnt = 0;
	node->size = SHELL_PARSE_NODE_SIZE;
	node->next = NULL;
	if (list)
	{
		if (!list->tail)
			list->head.next = node;
		if (list->tail)
			list->tail->next = node;
		list->tail = node;
		list->cnt += 1;
	}
	return (node);
}

// parse_list의 head는 더미노드라서 tail만 신경 씀
int	shell_parse_util_add_char(t_parse_list *list, char c)
{
	char			*ret;
	t_parse_node	*tail;

	if (!list->tail)
		shell_parse_util_append_new_node(list);
	tail = list->tail;
	if (tail->cnt == tail->size)
	{
		ret = malloc(sizeof(char) * tail->size * 2);
		if (NULL == ret)
			return (-1);
		ft_memcopy(ret, tail->str, tail->size);
		free(tail->str);
		tail->str = ret;
		tail->size *= 2;
	}
	tail->str[tail->cnt++] = c;
	return (0);
}

// parse_node에 담아둔 것은 정확한 크기를 모르고 malloc 한 거라
// parsing 다 돼서 정확한 크기를 알 수 있어, argv로 다시 깔끔하게 만듬
// 원래 list 내용물은 지워짐
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
		argv[cnt] = malloc(sizeof(char) * node->cnt + 1);
		if (NULL == argv[cnt])
		{
			free_cnt = -1;
			while (++free_cnt < cnt)
				free(argv[free_cnt]);
			return (NULL);
		}
		argv[node->cnt] = '\0';
		ft_memcopy(argv[cnt], node->str, node->cnt);
		list->head.next = node->next;
		free(node->str);
		free(node);
	}
	list->tail = NULL;
}
