/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_state6.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:34:57 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/26 22:54:40 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "shell_parse_state.h"
#include "shell_parse_util_node_list.h"

t_state_shell_parse	shell_parse_state6(t_state_shell_parse state,
			t_shell_data *p_data, char c)
{
	if (S_P_DQUOTE_QUOTE == state)
		return (shell_parse_dquote_quote(p_data, c));
	else if (S_P_REDIRECT_DQUOTE_QUOTE == state)
		return (shell_parse_redirect_dquote_quote(p_data, c));
	else if (S_P_REDIRECT_STRING_DQUOTE_QUOTE == state)
		return (shell_parse_redirect_string_dquote_quote(p_data, c));
	return (S_P_ERROR);
}

t_state_shell_parse	shell_parse_dquote_quote(t_shell_data *p_data, char c)
{
	if ('\'' == c)
		return (S_P_DQUOTE);
	if (shell_parse_node_add_char(p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (S_P_DQUOTE_QUOTE);
}

t_state_shell_parse	shell_parse_redirect_dquote_quote(t_shell_data *p_data,
						char c)
{
	if ('\'' == c)
		return (S_P_REDIRECT_DQUOTE);
	if (shell_parse_node_add_char(p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (S_P_REDIRECT_DQUOTE_QUOTE);
}

t_state_shell_parse	shell_parse_redirect_string_dquote_quote(
						t_shell_data *p_data, char c)
{
	if ('\'' == c)
		return (S_P_REDIRECT_STRING_DQUOTE);
	if (shell_parse_node_add_char(p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (S_P_REDIRECT_STRING_DQUOTE_QUOTE);
}
