/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_util_tree_push.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:20:23 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/24 20:25:03 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tree_heredoc/shell_tree.h"
#include "shell_parse_util_tree.h"

int	is_child_full(t_shell_tree_node *focus)
{
	if (focus->left && focus->right)
		return (1);
	return (0);
}

int	is_kind_bool(t_shell_tree_kind kind)
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

void	shell_parse_util_push_focus(t_shell_tree_node **p_focus,
				t_shell_tree_node *item)
{
	int push_left;

	push_left = 1;
	if (T_PIPE == item->kind)
		push_left = 0;
	shell_tree_insert_push_focus(p_focus, item, push_left);
}

void	shell_parse_util_push_chld(t_shell_tree_node **p_focus,
				t_shell_tree_node *item)
{
	int	push_left;
	int	append_left;

	push_left = 1;
	append_left = 1;
	if (T_ROOT == (*p_focus)->kind
		|| ((*p_focus)->left && !(*p_focus)->right))
		push_left = 0;
	if (T_PIPE == item->kind)
		append_left = 0;
	shell_tree_insert_push_child(p_focus, item, push_left, append_left);
}
