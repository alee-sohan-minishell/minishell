/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_util_tree_push.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:20:23 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/24 22:45:17 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tree_heredoc/shell_tree.h"
#include "shell_parse_util_tree.h"

int	is_full(t_shell_tree_node *focus)
{
	if (focus->left && focus->right)
		return (1);
	return (0);
}

int	is_left(t_shell_tree_node *focus)
{
	if (focus->left && !focus->right)
		return (1);
	return (0);
}

int	is_bool(t_shell_tree_kind kind)
{
	if (T_BOOL_AND == kind || T_BOOL_OR == kind)
		return (1);
	return (0);
}

void	shell_parse_util_push_replace(t_shell_tree_node **p_focus,
				t_shell_tree_node *item)
{
	(*p_focus)->kind = item->kind;
	(*p_focus)->argv = item->argv;
	(*p_focus)->fd = item->fd;
	(*p_focus)->filepath = item->filepath;
	return (tree_free(item, 0));
}

void	shell_parse_util_push_chld(t_shell_tree_node **p_f,
				t_shell_tree_node *item)
{
	int	push_left;

	push_left = 1;
	if ((T_EMPTY == (*p_f)->kind && is_left(*p_f))
		|| (T_PIPE == (*p_f)->kind && is_left(*p_f))
		|| (T_PIPE == (*p_f)->kind && is_full(*p_f))
		|| (is_bool((*p_f)->kind) && (*p_f)->left))
		push_left = 0;
	shell_tree_insert_push_child(p_f, item, push_left, 1);
}
