/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_util_tree.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 23:07:09 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/27 22:32:36 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../shell/shell.h"
#include "../tree_heredoc/shell_tree.h"
#include "shell_parse_util_node_list.h"
#include "shell_parse_state.h"
#include "shell_parse_util_tree_push.h"
#include "shell_parse_util_tree2.h"
#include "shell_parse_util_state2.h"

int	is_redirect(t_shell_tree_kind kind)
{
	if (T_REDIRECT_IN == kind || T_REDIRECT_OUT == kind
		|| T_REDIRECT_HEREDOC == kind || T_REDIRECT_APPEND == kind)
		return (1);
	return (0);
}

void	shell_parse_util_push_tree(t_shell_tree_node **p_f,
				t_shell_tree_node *item)
{
	if (T_EMPTY == (*p_f)->kind
		&& !(T_EMPTY == item->kind || T_COMMAND == item->kind))
		return (shell_parse_util_push_replace(p_f, item));
	else if ((T_EMPTY == (*p_f)->kind && is_full(*p_f))
		|| (T_PIPE == (*p_f)->kind && is_full(*p_f) && !is_redirect(item->kind))
		|| (is_bool((*p_f)->kind) && is_full(*p_f) && T_PIPE != item->kind)
		|| (is_redirect((*p_f)->kind) && !(*p_f)->left
			&& !(*p_f)->right && T_PIPE == item->kind)
		|| (is_redirect((*p_f)->kind) && (*p_f)->left
			&& !is_redirect(item->kind)))
		return (shell_tree_insert_push_focus(p_f, item, 1));
	shell_parse_util_push_chld(p_f, item);
}

int	shell_parse_util_insert_cmd(t_shell_data *p_data)
{
	char				**argv;
	t_shell_tree_node	*tree_node;

	argv = shell_parse_list_to_argv(&p_data->parse_list);
	if (NULL == argv)
		return (-1);
	tree_node = tree_new_node(T_COMMAND, argv, -1, NULL);
	if (NULL == tree_node)
	{
		shell_parse_util_argv_free(argv, -1);
		return (-1);
	}
	shell_parse_util_push_tree(&p_data->focus, tree_node);
	++p_data->cmd_count;
	return (0);
}

int	shell_parse_util_insert_redirect(t_shell_data *p_data)
{
	char				*str;
	t_shell_tree_node	*tree_node;

	str = shell_parse_node_to_str(p_data->parse_tmp);
	if (NULL == str)
		return (-1);
	p_data->parse_tmp = shell_parse_new_node();
	if (NULL == p_data->parse_tmp)
		return (-1);
	if (T_REDIRECT_HEREDOC == p_data->redirect_kind)
	{
		if (insert_heredoc_node(p_data, str))
			return (-1);
		str = make_heredoc_filename(&p_data->heredoc_cnt);
		if (NULL == str)
			return (-1);
	}
	tree_node = tree_new_node(p_data->redirect_kind, NULL, -1, str);
	if (NULL == tree_node)
		return (-1);
	shell_parse_util_push_tree(&p_data->focus, tree_node);
	return (0);
}

int	shell_parse_util_insert_argv_in_cmd(t_shell_data *p_data)
{
	char				*str;
	t_shell_tree_node	*tmp;

	tmp = p_data->focus->left;
	while (T_COMMAND != tmp->kind)
	{
		if (tmp->right)
			tmp = tmp->right;
		else
			tmp = tmp->left;
	}
	str = shell_parse_node_to_str(p_data->parse_tmp);
	if (NULL == str)
		return (-1);
	p_data->parse_tmp = shell_parse_new_node();
	tmp->argv = append_argv(tmp->argv, str);
	if (NULL == tmp->argv)
	{
		free(str);
		return (-1);
	}
	return (0);
}
