/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_state3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:34:57 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/27 22:43:05 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "shell_parse_state.h"
#include "../tree_heredoc/shell_tree.h"
#include "shell_parse_util_tree.h"
#include "shell_parse_util_state.h"
#include "shell_parse_util_node_list.h"

t_state_shell_parse	shell_parse_bool_and(t_shell_data *p_data, char c)
{
	t_shell_tree_node	*and;

	and = tree_new_node(T_BOOL_AND, NULL, -1, NULL);
	if (NULL == and)
		return (S_P_ERROR);
	shell_parse_util_push_tree(&p_data->focus, and);
	if (' ' == c || '\t' == c || '\'' == c || '"' == c || '$' == c
		|| '(' == c || ')' == c
		|| '|' == c || '<' == c || '>' == c)
		return (shell_parse_util_get_state(c));
	else if ('&' == c)
		return (S_P_ERROR);
	if (shell_parse_node_add_char(p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (S_P_STRING);
}

t_state_shell_parse	shell_parse_bool_or(t_shell_data *p_data, char c)
{
	t_shell_tree_node	*or;

	or = tree_new_node(T_BOOL_OR, NULL, -1, NULL);
	if (NULL == or)
		return (S_P_ERROR);
	shell_parse_util_push_tree(&p_data->focus, or);
	if (' ' == c || '\t' == c || '\'' == c || '"' == c || '$' == c
		|| '(' == c || ')' == c || '&' == c
		|| '<' == c || '>' == c)
		return (shell_parse_util_get_state(c));
	else if ('|' == c)
		return (S_P_ERROR);
	if (shell_parse_node_add_char(p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (S_P_STRING);
}

t_state_shell_parse	shell_parse_redirect_heredoc(t_shell_data *p_data, char c)
{
	p_data->redirect_kind = T_REDIRECT_HEREDOC;
	if (p_data->parse_tmp->cnt == 0 && (' ' == c || '\t' == c))
		return (S_P_REDIRECT_HEREDOC);
	else if (' ' == c || '\t' == c || '(' == c || ')' == c
		|| '&' == c || '|' == c
		|| '<' == c || '>' == c)
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
	if (shell_parse_node_add_char(p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (S_P_REDIRECT_HEREDOC);
}

t_state_shell_parse	shell_parse_redirect_append(t_shell_data *p_data, char c)
{
	p_data->redirect_kind = T_REDIRECT_APPEND;
	if (p_data->parse_tmp->cnt == 0 && (' ' == c || '\t' == c))
		return (S_P_REDIRECT_APPEND);
	else if (' ' == c || '\t' == c || '(' == c || ')' == c
		|| '&' == c || '|' == c
		|| '<' == c || '>' == c)
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
	if (shell_parse_node_add_char(p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (S_P_REDIRECT_APPEND);
}

t_state_shell_parse	shell_parse_dquote_env(t_shell_data *p_data, char c)
{
	if (p_data->parse_env->cnt == 0
		&& (' ' == c || '\t' == c || '"' == c || '?' == c))
		return (treat_first_dquote_env(p_data, c));
	if (' ' == c || '\t' == c || '\'' == c || '"' == c || '$' == c
		|| '(' == c || ')' == c || '&' == c
		|| '|' == c || '<' == c || '>' == c
		|| '-' == c)
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
