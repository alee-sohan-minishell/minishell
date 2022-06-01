/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_state3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:34:57 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/05 16:46:39 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "shell_parse_state.h"
#include "../tree/shell_tree.h"
#include "shell_parse_utils1.h"

t_state_shell_parse	shell_parse_and(t_shell_data *p_data, char *s)
{
	t_state_shell_parse	next_state;

	next_state = shell_parse_util_strcmp(S_P_PIPE, s);
	if (S_P_BOOL_AND == next_state)
		return (S_P_BOOL_AND);
	return (S_P_ERROR);
}

t_state_shell_parse	shell_parse_pipe(t_shell_data *p_data, char *s)
{
	t_state_shell_parse	next_state;
	t_shell_tree_node	*pipe;

	pipe = tree_new_node(T_PIPE, NULL, 0, NULL);
	if (NULL == pipe)
		return (S_P_ERROR);
	tree_insert(&p_data->focus, pipe);
	next_state = shell_parse_util_strcmp(S_P_PIPE, s);
	if (S_P_STRING == next_state)
	{
		if (shell_parse_util_add_char(&p_data->parse_list, *s))
			return (S_P_ERROR);
	}
	else if (S_P_CLOSE == next_state || S_P_AND == next_state
		|| S_P_PIPE == next_state || S_P_BOOL_AND == next_state
		|| S_P_BOOL_OR == next_state || S_P_DQUOTE_ENV == next_state)
		return (S_P_ERROR);
	return (next_state);
}

t_state_shell_parse	shell_parse_redirect_in(t_shell_data *p_data, char *s)
{
	// TODO
}

t_state_shell_parse	shell_parse_redirect_out(t_shell_data *p_data, char *s)
{
	// TODO
}

t_state_shell_parse	shell_parse_finsih(t_shell_data *p_data, char *s)
{
	// TODO
}
