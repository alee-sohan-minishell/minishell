/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_node_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 20:03:33 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/21 20:41:23 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell_parse_node_list.h"

t_parse_node	*shell_parse_new_node()
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
	ret->cnt = 0;
	ret->size = SHELL_PARSE_NODE_SIZE;
	ret->next = NULL;
	ret->pre = NULL;
	return (ret);
}

void	shell_parse_node_free(t_parse_node *node)
{
	if (node)
	{
		if (node->str)
			free(node->str);
		free(node);
	}
}

// 원래 node 그대로 list로 감, 원래 node 자리에 새로 동적할당
int	shell_parse_list_append_node(t_parse_list *list, t_parse_node **p_node)
{
	(*p_node)->pre = list->tail.pre;
	(*p_node)->next = &list->tail;
	list->tail.pre->next = *p_node;
	list->tail.pre = *p_node;
	++(list->cnt);
	*p_node = shell_parse_new_node();
	if (NULL == *p_node)
		return (-1);
	return (0);
}

void	shell_parse_list_free(t_parse_list *list)
{
	t_parse_node	*node;

	node = list->head.next;
	while (node != &list->tail)
	{
		list->head.next = node->next;
		shell_parse_node_free(node);
		node = list->head.next;
	}
	list->tail.pre = &list->head;
	list->cnt = 0;
}
