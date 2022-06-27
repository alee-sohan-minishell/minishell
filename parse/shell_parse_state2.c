/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_state2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:34:57 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/27 22:45:25 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "shell_parse_state.h"
#include "shell_parse_util_state.h"
#include "shell_parse_util_node_list.h"
#include "../tree_heredoc/shell_tree.h"
#include "shell_parse_util_tree.h"

t_state_shell_parse	shell_parse_close(t_shell_data *p_data, char c)
{
	if (p_data->focus->parent)
		p_data->focus = p_data->focus->parent;
	if (' ' == c || '\t' == c || '\'' == c || '"' == c || '$' == c
		|| '(' == c || ')' == c || '&' == c
		|| '|' == c || '<' == c || '>' == c)
		return (shell_parse_util_get_state(c));
	if (shell_parse_node_add_char(p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (S_P_STRING);
}

t_state_shell_parse	shell_parse_and(t_shell_data *p_data, char c)
{
	if (p_data)
		if ('&' == c)
			return (S_P_BOOL_AND);
	return (S_P_ERROR);
}

t_state_shell_parse	shell_parse_pipe(t_shell_data *p_data, char c)
{
	t_shell_tree_node	*pipe;

	if ('|' == c)
		return (S_P_BOOL_OR);
	pipe = tree_new_node(T_PIPE, NULL, -1, NULL);
	if (NULL == pipe)
		return (S_P_ERROR);
	++p_data->pipe_count;
	pipe->pnum = p_data->pipe_count;
	shell_parse_util_push_tree(&p_data->focus, pipe);
	if (' ' == c || '\t' == c || '\'' == c || '"' == c || '$' == c
		|| '(' == c || '<' == c || '>' == c)
		return (shell_parse_util_get_state(c));
	else if (')' == c || '&' == c)
		return (S_P_ERROR);
	if (shell_parse_node_add_char(p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (S_P_STRING);
}

t_state_shell_parse	shell_parse_redirect_in(t_shell_data *p_data, char c)
{
	p_data->redirect_kind = T_REDIRECT_IN;
	if (p_data->parse_tmp->cnt == 0 && (' ' == c || '\t' == c))
		return (S_P_REDIRECT_IN);
	else if (' ' == c || '\t' == c || '(' == c || ')' == c
		|| '&' == c || '|' == c || '>' == c)
	{
		if (shell_parse_util_insert_redirect(p_data))
			return (S_P_ERROR);
		p_data->redirect_kind = T_EMPTY;
		if (' ' == c || '\t' == c)
			return (S_P_REDIRECT_STRING);
		return (shell_parse_util_get_state(c));
	}
	else if ('\'' == c)
		return (S_P_REDIRECT_QUOTE);
	else if ('"' == c)
		return (S_P_REDIRECT_DQUOTE);
	else if ('$' == c)
		return (S_P_REDIRECT_ENV);
	else if ('<' == c)
		return (S_P_REDIRECT_HEREDOC);
	if (shell_parse_node_add_char(p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (S_P_REDIRECT_IN);
}

t_state_shell_parse	shell_parse_redirect_out(t_shell_data *p_data, char c)
{
	p_data->redirect_kind = T_REDIRECT_OUT;
	if (p_data->parse_tmp->cnt == 0 && (' ' == c || '\t' == c))
		return (S_P_REDIRECT_OUT);
	else if (' ' == c || '\t' == c || '(' == c || ')' == c
		|| '&' == c || '|' == c || '<' == c)
	{
		if (shell_parse_util_insert_redirect(p_data))
			return (S_P_ERROR);
		p_data->redirect_kind = T_EMPTY;
		if (' ' == c || '\t' == c)
			return (S_P_REDIRECT_STRING);
		return (shell_parse_util_get_state(c));
	}
	else if ('\'' == c)
		return (S_P_REDIRECT_QUOTE);
	else if ('"' == c)
		return (S_P_REDIRECT_DQUOTE);
	else if ('$' == c)
		return (S_P_REDIRECT_ENV);
	else if ('>' == c)
		return (S_P_REDIRECT_APPEND);
	if (shell_parse_node_add_char(p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (S_P_REDIRECT_OUT);
}
