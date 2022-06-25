/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 21:00:46 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/25 23:08:58 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell_heredoc.h"

t_shell_heredoc_node	*heredoc_new_node(char *delimiter)
{
	t_shell_heredoc_node	*node;

	node = malloc(sizeof(t_shell_heredoc_node));
	if (NULL == node)
		return (NULL);
	node->next = NULL;
	node->delimiter = delimiter;
	return (node);
}

void	heredoc_node_free(t_shell_heredoc_node *node)
{
	if (node->delimiter)
		free(node->delimiter);
	free(node);
}

void	heredoc_list_add(t_shell_heredoc_list *list, t_shell_heredoc_node *node)
{
	node->pre = list->tail.pre;
	node->next = &list->tail;
	list->tail.pre->next = node;
	list->tail.pre = node;
	++list->cnt;
}

void	heredoc_list_free(t_shell_heredoc_list *list)
{
	t_shell_heredoc_node	*node;

	node = list->head.next;
	while (node != &list->tail)
	{
		list->head.next = node->next;
		heredoc_node_free(node);
		node = list->head.next;
	}
	list->tail.pre = &list->head;
}
