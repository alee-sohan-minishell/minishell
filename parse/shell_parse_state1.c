/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_state1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:34:57 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/18 07:07:04 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "shell_parse_state.h"
#include "shell_parse_utils1.h"
#include "shell_parse_utils2.h"
#include "shell_parse_utils3.h"

/*
if (' ' == c || '\'' == c || '"' == c || '$' == c
	|| '(' == c || ')' == c || '&' == c
	|| '|' == c || '<' == c || '>' == c)
*/

t_state_shell_parse	shell_parse_space(t_shell_data *p_data, char c)
{
	if (' ' == c || '\'' == c || '"' == c || '$' == c
		|| '<' == c || '>' == c)
		return (shell_parse_util_get_state(c));
	else if ('(' == c || ')' == c || '&' == c || '|' == c)
	{
		if (NULL != p_data->parse_list.tail)
			if (shell_parse_util_insert_cmd(p_data))
				return (S_P_ERROR);
		return (shell_parse_util_get_state(c));
	}
	if (shell_parse_util_add_char(&p_data->parse_list, c))
		return (S_P_ERROR);
	return (S_P_STRING);
}

t_state_shell_parse	shell_parse_quote(t_shell_data *p_data, char c)
{
	if ('\'' == c)
		return (S_P_STRING);
	if (shell_parse_util_add_char(&p_data->parse_list, c))
		return (S_P_ERROR);
	return (S_P_QUOTE);
}

t_state_shell_parse	shell_parse_dquote(t_shell_data *p_data, char c)
{
	if ('"' == c)
		return (S_P_STRING);
	else if ('$' == c)
		return (S_P_DQUOTE_ENV);
	if (shell_parse_util_add_char(&p_data->parse_list, c))
		return (S_P_ERROR);
	return (S_P_DQUOTE);
}

t_state_shell_parse	shell_parse_env(t_shell_data *p_data, char c)
{
	if (' ' == c && p_data->parse_env.cnt == 0) // 일반적이지 않은 상황
	{
		if (shell_parse_util_add_char(&p_data->parse_list, '$'))
			return (S_P_ERROR);
		if (NULL == shell_parse_util_append_new_node(&p_data->parse_list))
			return (S_P_ERROR);
		return (S_P_SPACE);
	}
	else if (' ' == c || '\'' == c || '"' == c || '$' == c
		|| '(' == c || ')' == c || '&' == c
		|| '|' == c || '<' == c || '>' == c) // 일반적이면서 env 끝나는 상황
	{
		if (shell_parse_util_env_convert(p_data))
			return (S_P_ERROR);
		if (' ' == c ||  '(' == c || ')' == c
			|| '&' == c || '|' == c || '<' == c || '>' == c)
		{
			if (NULL == shell_parse_util_append_new_node(&p_data->parse_list))
				return (S_P_ERROR);
		}
		return (shell_parse_util_get_state(c));
	}
	if (shell_parse_util_env_add_char(&p_data->parse_env, c))
		return (S_P_ERROR);
	return (S_P_ENV);
}

t_state_shell_parse	shell_parse_dquote_env(t_shell_data *p_data, char c)
{
	if (' ' == c || '\'' == c || '"' == c || '$' == c
		|| '(' == c || ')' == c || '&' == c
		|| '|' == c || '<' == c || '>' == c)
	{
		if (shell_parse_util_env_convert(p_data))
			return (S_P_ERROR);
		if ('"' == c)
			reuturn (S_P_STRING);
		if (shell_parse_util_env_add_char(&p_data->parse_env, c))
			return (S_P_ERROR);
		return (S_P_DQUOTE);
	}
	if (shell_parse_util_env_add_char(&p_data->parse_env, c))
		return (S_P_ERROR);
	return (S_P_ENV);
}
