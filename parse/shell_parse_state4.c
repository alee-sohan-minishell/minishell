/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_state4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:34:57 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/28 21:52:47 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "shell_parse_state.h"
#include "shell_parse_util_state.h"
#include "shell_parse_util_state2.h"
#include "shell_parse_util_node_list.h"
#include "shell_parse_util_tree.h"
#include "shell_parse_util_tree2.h"

t_state_shell_parse	shell_parse_redirect_env(t_shell_data *p_data, char c)
{
	if (p_data->parse_env->cnt == 0 && (' ' == c || '\t' == c || '?' == c))
		return (treat_first_redirect_env(p_data, c));
	else if (' ' == c || '\t' == c || '\'' == c || '"' == c || '$' == c
		|| '(' == c || ')' == c || '&' == c
		|| '|' == c || '<' == c || '>' == c)
	{
		if (shell_parse_find_str_in_env(p_data))
			return (S_P_ERROR);
		if ('\'' == c)
			return (S_P_REDIRECT_QUOTE);
		else if ('"' == c)
			return (S_P_REDIRECT_DQUOTE);
		else if ('$' == c)
			return (S_P_REDIRECT_ENV);
		if (shell_parse_util_insert_redirect(p_data))
			return (S_P_ERROR);
		p_data->redirect_kind = T_EMPTY;
		if (' ' == c || '\t' == c)
			return (S_P_REDIRECT_STRING);
		return (shell_parse_util_get_state(c));
	}
	if (shell_parse_node_add_char(p_data->parse_env, c))
		return (S_P_ERROR);
	return (S_P_REDIRECT_ENV);
}

t_state_shell_parse	shell_parse_redirect_quote(t_shell_data *p_data, char c)
{
	if ('\'' == c)
		return (get_redirect_state(p_data->redirect_kind));
	if (shell_parse_node_add_char(p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (S_P_REDIRECT_QUOTE);
}

t_state_shell_parse	shell_parse_redirect_dquote(t_shell_data *p_data, char c)
{
	if ('"' == c)
		return (get_redirect_state(p_data->redirect_kind));
	else if ('$' == c)
		return (S_P_REDIRECT_DQUOTE_ENV);
	if (shell_parse_node_add_char(p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (S_P_REDIRECT_DQUOTE);
}

t_state_shell_parse	shell_parse_redirect_dquote_env(t_shell_data *p_data,
						char c)
{
	if (p_data->parse_env->cnt == 0
		&& (' ' == c || '\t' == c || '"' == c || '?' == c))
		return (treat_first_redirect_dquote_env(p_data, c));
	else if (' ' == c || '\t' == c || '\'' == c || '"' == c || '$' == c
		|| '(' == c || ')' == c || '&' == c
		|| '|' == c || '<' == c || '>' == c)
	{
		if (shell_parse_find_str_in_env(p_data))
			return (S_P_ERROR);
		if ('"' == c)
			return (get_redirect_state(p_data->redirect_kind));
		else if ('$' == c)
			return (S_P_REDIRECT_DQUOTE_ENV);
		if (shell_parse_node_add_char(p_data->parse_tmp, c))
			return (S_P_ERROR);
		return (S_P_REDIRECT_DQUOTE);
	}
	if (shell_parse_node_add_char(p_data->parse_env, c))
		return (S_P_ERROR);
	return (S_P_REDIRECT_DQUOTE_ENV);
}

t_state_shell_parse	shell_parse_redirect_string(t_shell_data *p_data, char c)
{
	if (p_data->parse_tmp->cnt == 0 && (' ' == c || '\t' == c))
		return (S_P_REDIRECT_STRING);
	else if ('\'' == c)
		return (S_P_REDIRECT_STRING_QUOTE);
	else if ('"' == c)
		return (S_P_REDIRECT_STRING_DQUOTE);
	else if ('$' == c)
		return (S_P_REDIRECT_STRING_ENV);
	else if (' ' == c || '\t' == c || '(' == c || ')' == c
		|| '&' == c || '|' == c || '<' == c || '>' == c)
	{
		if (p_data->parse_tmp->cnt)
		{
			if (shell_parse_util_insert_argv_in_cmd(p_data))
				return (S_P_ERROR);
		}
		if (' ' == c || '\t' == c)
			return (S_P_REDIRECT_STRING);
		return (shell_parse_util_get_state(c));
	}
	if (shell_parse_node_add_char(p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (S_P_REDIRECT_STRING);
}
