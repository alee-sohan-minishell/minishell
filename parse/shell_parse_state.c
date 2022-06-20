/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:40:49 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/20 21:57:04 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_parse_state.h"

t_state_shell_parse	shell_parse_state1(t_state_shell_parse state,
			t_shell_data *p_data, char c)
{
	if (S_P_SPACE == state)
		return (shell_parse_space(p_data, c));
	else if (S_P_QUOTE == state)
		return (shell_parse_quote(p_data, c));
	else if (S_P_DQUOTE == state)
		return (shell_parse_dquote(p_data, c));
	else if (S_P_ENV == state)
		return (shell_parse_env(p_data, c));
	else if (S_P_DQUOTE_ENV == state)
		return (shell_parse_dquote_env(p_data, c));
}

t_state_shell_parse	shell_parse_state2(t_state_shell_parse state,
			t_shell_data *p_data, char c)
{
	if (S_P_OPEN == state)
		return (shell_parse_open(p_data, c));
	else if (S_P_CLOSE == state)
		return (shell_parse_close(p_data, c));
	else if (S_P_REDIRECT_SPACE == state)
		return (shell_parse_redirect_space(p_data, c));
}

t_state_shell_parse	shell_parse_state3(t_state_shell_parse state,
			t_shell_data *p_data, char c)
{
	if (S_P_AND == state)
		return (shell_parse_and(p_data, c));
	else if (S_P_PIPE == state)
		return (shell_parse_pipe(p_data, c));
	else if (S_P_REDIRECT_IN == state)
		return (shell_parse_redirect_in(p_data, c));
	else if (S_P_REDIRECT_OUT == state)
		return (shell_parse_redirect_out(p_data, c));
}

t_state_shell_parse	shell_parse_state4(t_state_shell_parse state,
			t_shell_data *p_data, char c)
{
	if (S_P_BOOL_AND == state)
		return (shell_parse_bool_and(p_data, c));
	else if (S_P_BOOL_OR == state)
		return (shell_parse_bool_or(p_data, c));
	else if (S_P_REDIRECT_HEREDOC == state)
		return (shell_parse_redirect_heredoc(p_data, c));
	else if (S_P_REDIRECT_APPEND == state)
		return (shell_parse_redirect_append(p_data, c));
	else if (S_P_STRING == state)
		return (shell_parse_string(p_data, c));
}
