/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_state2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:34:57 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/21 15:05:55 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "shell_parse_state.h"
#include "shell_parse_util_state.h"
#include "../tree_heredoc/shell_tree.h"
#include "../parse/shell_parse_util_tree.h"
#include "shell_parse_util_node_list.h"

t_state_shell_parse	shell_parse_open(t_shell_data *p_data, char c)
{
	t_shell_tree_node	*empty;

	if (' ' == c || '\'' == c || '"' == c || '$' == c
		|| '(' == c || ')' == c
		|| '<' == c || '>' == c)
	{
		empty = tree_new_node(T_EMPTY, NULL, -1, NULL);
		shell_parse_util_push_tree(&p_data->focus, empty);
		if (NULL == empty)
			return (S_P_ERROR);
		return (shell_parse_util_get_state(c));
	}
	else if ('&' == c || '|' == c)
		return (S_P_ERROR);
	empty = tree_new_node(T_EMPTY, NULL, -1, NULL);
	if (NULL == empty)
		return (S_P_ERROR);
	shell_parse_util_push_tree(&p_data->focus, empty);
	if (shell_parse_node_add_char(p_data->parse_env, c))
		return (S_P_ERROR);
	return (S_P_STRING);
}

t_state_shell_parse	shell_parse_close(t_shell_data *p_data, char c)
{
	if (p_data->focus->parent)
		p_data->focus = p_data->focus->parent;
	if (' ' == c || '\'' == c || '"' == c || '$' == c
		|| '(' == c || ')' == c || '&' == c
		|| '|' == c || '<' == c || '>' == c)
		return (shell_parse_util_get_state(c));
	if (shell_parse_node_add_char(p_data->parse_env, c))
		return (S_P_ERROR);
	return (S_P_STRING);
}
