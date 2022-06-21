/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_state1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:34:57 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/21 23:22:13 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "shell_parse_state.h"
#include "shell_parse_util_state.h"
#include "shell_parse_node_list.h"
#include "shell_parse_util_node_list.h"
#include "shell_parse_util_tree.h"

/*
if (' ' == c || '\'' == c || '"' == c || '$' == c
	|| '(' == c || ')' == c || '&' == c
	|| '|' == c || '<' == c || '>' == c)
*/

// 한 문장 끝나는 상황에서만 insert_cmd
// 한 단어 끝나야 list_append_node
// 한 글자씩은 add_char

// TODO tab 넣어야 함함

t_state_shell_parse	shell_parse_space(t_shell_data *p_data, char c)
{
	if (' ' == c || '\'' == c || '"' == c || '$' == c)
		return (shell_parse_util_get_state(c));
	else if ('(' == c || ')' == c || '&' == c || '|' == c
		|| '<' == c || '>' == c)
	{
		if (p_data->parse_list.cnt)
			if (shell_parse_util_insert_cmd(p_data))
				return (S_P_ERROR);
		return (shell_parse_util_get_state(c));
	}
	if (shell_parse_node_add_char(p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (S_P_STRING);
}

t_state_shell_parse	shell_parse_quote(t_shell_data *p_data, char c)
{
	if ('\'' == c)
		return (S_P_STRING);
	if (shell_parse_node_add_char(p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (S_P_QUOTE);
}

t_state_shell_parse	shell_parse_dquote(t_shell_data *p_data, char c)
{
	if ('"' == c)
		return (S_P_STRING);
	else if ('$' == c)
		return (S_P_DQUOTE_ENV);
	if (shell_parse_node_add_char(p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (S_P_DQUOTE);
}

t_state_shell_parse	shell_parse_env(t_shell_data *p_data, char c)
{
	if (' ' == c && p_data->parse_env->cnt == 0) // 일반적이지 않은 상황, ls$ -la 같은 경우, env 문자 담은거 아무 것도 없을 때 (처음 시작할 때)
	{
		if (shell_parse_node_add_char(p_data->parse_tmp, '$')) // $를 문자 취급해서 add 한다
			return (S_P_ERROR);
		if (shell_parse_list_append_node(&p_data->parse_list, &(p_data->parse_tmp)))
			return (S_P_ERROR);
		return (S_P_SPACE);
	}
	else if (' ' == c || '\'' == c || '"' == c || '$' == c // 공백이 위에도 있지만 여기 이미 env 몇 글자 들어온 상황 때문에 또 있음
		|| '(' == c || ')' == c || '&' == c
		|| '|' == c || '<' == c || '>' == c) // 일반적이면서 env 끝나는 상황
	{
		if (shell_parse_find_str_in_env(p_data)) // p_data->parse_env에 있는 문자 key로 env 찾아서 p_data->parse_tmp에 바로 add_char 함
			return (S_P_ERROR);
		if (' ' == c || '(' == c || ')' == c
			|| '&' == c || '|' == c || '<' == c || '>' == c)
		{
			if (shell_parse_list_append_node(&p_data->parse_list,
				&(p_data->parse_tmp)))
				return (S_P_ERROR);
			if (' ' != c)
				if (shell_parse_util_insert_cmd(p_data))
					return (S_P_ERROR);
		}
		return (shell_parse_util_get_state(c));
	}
	if (shell_parse_node_add_char(p_data->parse_env, c))
		return (S_P_ERROR);
	return (S_P_ENV);
}

t_state_shell_parse	shell_parse_dquote_env(t_shell_data *p_data, char c)
{
	if ('"' == c && p_data->parse_env->cnt == 0)
	{
		if (shell_parse_node_add_char(p_data->parse_tmp, '$'))
			return (S_P_ERROR);
		return (S_P_STRING);
	}
	if (' ' == c || '\'' == c || '"' == c || '$' == c
		|| '(' == c || ')' == c || '&' == c
		|| '|' == c || '<' == c || '>' == c)
	{
		if (shell_parse_find_str_in_env(p_data))
			return (S_P_ERROR);
		if ('"' == c)
			return (S_P_STRING);
		else if ('$' == c)
			return (S_P_DQUOTE_ENV);
		if (shell_parse_node_add_char(p_data->parse_tmp, c))
			return (S_P_ERROR);
		return (S_P_DQUOTE);
	}
	if (shell_parse_node_add_char(p_data->parse_env, c))
		return (S_P_ERROR);
	return (S_P_DQUOTE_ENV);
}
