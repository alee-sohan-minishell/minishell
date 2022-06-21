/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_state5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:34:57 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/20 19:43:26 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_parse_state.h"
#include "shell_parse_util_tree.h"

t_state_shell_parse	shell_parse_redirect_env(t_shell_data *p_data, char c)
{
	if (' ' == c || '\'' == c || '"' == c || '$' == c
		|| '(' == c || ')' == c || '&' == c
		|| '|' == c || '<' == c || '>' == c)


	if (' ' == c && p_data->parse_env->cnt == 0)
		return (S_P_ERROR);
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
				p_data->parse_tmp))
				return (S_P_ERROR);
			if (' ' != c)
				if (shell_parse_util_insert_cmd(p_data))
					return (S_P_ERROR);
		}
		return (shell_parse_util_get_state(c));
	}
	if (shell_parse_node_add_char(&p_data->parse_env, c))
		return (S_P_ERROR);
	return (S_P_ENV);



	if (' ' == c || '\'' == c || '"' == c || '$' == c)
		return (shell_parse_util_get_state(c));
	else if ('(' == c || ')' == c || '&' == c || '|' == c)
	{
		if (NULL != p_data->parse_list.tail)
			if (shell_parse_util_insert_cmd(p_data))
				return (S_P_ERROR);
		return (shell_parse_util_get_state(c));
	}
	else if ('<' == c || '>' == c)
	if (shell_parse_node_add_char(&p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (S_P_STRING);
}

t_state_shell_parse	shell_parse_redirect_quote(t_shell_data *p_data, char c)
{

}

t_state_shell_parse	shell_parse_redirect_dquote(t_shell_data *p_data, char c)
{

}

t_state_shell_parse	shell_parse_redirect_dquote_env(t_shell_data *p_data,
						char c)
{

}
