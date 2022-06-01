/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_state2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:34:57 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/05 16:46:21 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "shell_parse_state.h"

#include "../tree/shell_tree.h"
#include "shell_parse_utils1.h"

// string state에서 이쪽으로 넘어오진 않음 공백 없고 바로 다른 문자랑 붙은 경우 string 취급됨
// echo test~
// ehoc test ~ //#
t_state_shell_parse	shell_parse_sharp(t_shell_data *p_data, char *s)
{
	// TODO
}

// string state에서 이쪽으로 넘어오진 않음 공백 없고 바로 다른 문자랑 붙은 경우 string 취급됨
// echo test~
// ehoc test ~ //#
t_state_shell_parse	shell_parse_dash(t_shell_data *p_data, char *s)
{
	// TODO
}

// string state에서 이쪽으로 넘어오진 않음 공백 없고 바로 다른 문자랑 붙은 경우 string 취급됨
// echo test~
// ehoc test ~ //#
t_state_shell_parse	shell_parse_tilda(t_shell_data *p_data, char *s)
{
	// TODO
}

t_state_shell_parse	shell_parse_open(t_shell_data *p_data, char *s)
{
	t_state_shell_parse	next_state;
	t_shell_tree_node	*empty;

	empty = tree_new_node(T_EMPTY, NULL, 0, NULL);
	if (NULL == empty)
		return (S_P_ERROR);
	tree_insert(&p_data->focus, empty);
	next_state = shell_parse_util_strcmp(S_P_OPEN, s);
	if (S_P_STRING == next_state)
	{
		if (shell_parse_util_add_char(&p_data->parse_list, *s))
			return (S_P_ERROR);
	}
	else if (S_P_SHARP == next_state || S_P_DASH == next_state
		|| S_P_TILDA == next_state || S_P_AND == next_state
		|| S_P_PIPE == next_state || S_P_BOOL_AND == next_state
		|| S_P_BOOL_OR == next_state || S_P_DQUOTE_ENV == next_state)
		return (S_P_ERROR);
	return (next_state);
}

t_state_shell_parse	shell_parse_close(t_shell_data *p_data, char *s)
{
	t_state_shell_parse	next_state;

	p_data->focus = p_data->focus->parent;
	next_state = shell_parse_util_strcmp(S_P_CLOSE, s);
	if (S_P_STRING == next_state)
	{
		if (shell_parse_util_add_char(&p_data->parse_list, *s))
			return (S_P_ERROR);
	}
	else if (S_P_QUOTE == next_state || S_P_DQUOTE == next_state
		|| S_P_ENV == next_state || S_P_DASH == next_state
		|| S_P_TILDA == next_state || S_P_OPEN == next_state
		|| S_P_DQUOTE_ENV == next_state)
		return (S_P_ERROR);
	return (next_state);
}
