/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_state4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:34:57 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/21 14:21:47 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "shell_parse_state.h"
#include "shell_parse_util_state.h"
#include "shell_parse_node_list.h"
#include "shell_parse_util_tree.h"

t_state_shell_parse	shell_parse_bool_and(t_shell_data *p_data, char c)
{
	if (' ' == c)
		return (S_P_BOOL_AND);
	else if (' ' == c || '\'' == c || '"' == c || '$' == c
		|| '(' == c || ')' == c
		|| '|' == c || '<' == c || '>' == c)
		return (shell_parse_util_get_state(c));
	else if ('&' == c)
		return (S_P_ERROR);
	if (shell_parse_node_add_char(&p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (S_P_STRING);
}

t_state_shell_parse	shell_parse_bool_or(t_shell_data *p_data, char c)
{
	if (' ' == c)
		return (S_P_BOOL_AND);
	else if (' ' == c || '\'' == c || '"' == c || '$' == c
		|| '(' == c || ')' == c || '&' == c
		|| '<' == c || '>' == c)
		return (shell_parse_util_get_state(c));
	else if ('|' == c)
		return (S_P_ERROR);
	if (shell_parse_node_add_char(&p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (S_P_STRING);
}

t_state_shell_parse	shell_parse_redirect_heredoc(t_shell_data *p_data, char c)
{
	p_data->redirect_kind = S_P_REDIRECT_HEREDOC;
	if (' ' == c &&  p_data->parse_tmp->cnt == 0)
		return (S_P_REDIRECT_HEREDOC);
	else if (' ' == c)
	{
		if (shell_parse_util_insert_redirect(p_data))
			return (S_P_ERROR);
		p_data->redirect_kind = T_EMPTY;
		return (S_P_SPACE);
	}
	else if ('\'' == c)
		return (S_P_REDIRECT_QUOTE);
	else if ('"' == c)
		return (S_P_REDIRECT_DQUOTE);
	else if ('$' == c)
		return (S_P_REDIRECT_ENV);
	else if ('(' == c || ')' == c || '&' == c || '|' == c
		|| '<' == c || '>' == c)
		return (S_P_ERROR);
	if (shell_parse_node_add_char(&p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (S_P_REDIRECT_HEREDOC);
}

t_state_shell_parse	shell_parse_redirect_append(t_shell_data *p_data, char c)
{
	p_data->redirect_kind = S_P_REDIRECT_APPEND;
	if (' ' == c &&  p_data->parse_tmp->cnt == 0)
		return (S_P_REDIRECT_APPEND);
	else if (' ' == c)
	{
		if (shell_parse_util_insert_redirect(p_data))
			return (S_P_ERROR);
		p_data->redirect_kind = T_EMPTY;
		return (S_P_SPACE);
	}
	else if ('\'' == c)
		return (S_P_REDIRECT_QUOTE);
	else if ('"' == c)
		return (S_P_REDIRECT_DQUOTE);
	else if ('$' == c)
		return (S_P_REDIRECT_ENV);
	else if ('(' == c || ')' == c || '&' == c || '|' == c
		|| '<' == c || '>' == c)
		return (S_P_ERROR);
	if (shell_parse_node_add_char(&p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (S_P_REDIRECT_APPEND);
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
