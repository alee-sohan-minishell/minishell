/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 21:00:46 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/01 21:19:31 by min-jo           ###   ########.fr       */
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
	node->delimiter = NULL;
	return (node);
}

void	heredoc_insert(t_shell_heredoc_node **focus, t_shell_heredoc_node *item)
{
	if (NULL == *focus)
	{
		*focus = item;
		return ;
	}
	(*focus)->next = item;
}

void	heredoc_delete(t_shell_heredoc_node *heredoc)
{
	while (heredoc)
	{
		free(heredoc->delimiter);
		heredoc = heredoc->next;
	}
}
