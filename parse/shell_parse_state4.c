/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_state4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:34:57 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/20 19:43:26 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "shell_parse_state.h"
#include "shell_parse_util_state.h"
#include "shell_parse_node_list.h"
#include "shell_parse_util_tree.h"

t_state_shell_parse	shell_parse_bool_and(t_shell_data *p_data, char c)
{
	// TODO
}

t_state_shell_parse	shell_parse_bool_or(t_shell_data *p_data, char c)
{
	// TODO
}

t_state_shell_parse	shell_parse_redirect_heredoc(t_shell_data *p_data, char c)
{
	//# TODO 리다이렉트인 경우 포커스가 밀려나는게 아니라 자식을 밀어냄
	//# TODO 커맨드가 아니면 포커스는 넣은 것


	// 임시 node에 add_char 하다가 list로 넣을지, redirect tree_insert 할지 결정하자
	if (' ' == c)
		return (S_P_REDIRECT_SPACE);
	else if ('\'' == c || '"' == c || '$' == c)
		return (shell_parse_util_get_state(c));
	else if ('<' == c)
		return (S_P_REDIRECT_HEREDOC);
	else if ('(' == c || ')' == c || '&' == c || '|' == c || '>' == c)
		return (S_P_ERROR);
	if (shell_parse_node_add_char(&p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (S_P_REDIRECT_IN);
}

t_state_shell_parse	shell_parse_redirect_append(t_shell_data *p_data, char c)
{
	// TODO
}

t_state_shell_parse	shell_parse_string(t_shell_data *p_data, char c)
{
	if (' ' == c)
	{
		if (shell_parse_list_append_node(&p_data->parse_list,
				p_data->parse_tmp))
			return (S_P_ERROR);
		return (S_P_SPACE);
	}
	else if ('\'' == c || '"' == c || '$' == c)
		return (shell_parse_util_get_state(c));
	else if ('(' == c || ')' == c || '&' == c
		|| '|' == c || '<' == c || '>' == c)
	{
		if (shell_parse_list_append_node(&p_data->parse_list,
				p_data->parse_tmp))
			return (S_P_ERROR);
		if (shell_parse_util_insert_cmd(p_data))
			return (S_P_ERROR);
		return (shell_parse_util_get_state(c));
	}
	if (shell_parse_node_add_char(&p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (S_P_STRING);
}
