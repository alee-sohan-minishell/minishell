/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_state1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:34:57 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/27 22:53:42 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "shell_parse_state.h"
#include "shell_parse_util_state.h"
#include "shell_parse_util_tree.h"
#include "shell_parse_util_node_list.h"
#include "shell_parse_node_list.h"
#include "../tree_heredoc/shell_tree.h"

/*
if (' ' == c || '\t' == c || '\'' == c || '"' == c || '$' == c
	|| '(' == c || ')' == c || '&' == c
	|| '|' == c || '<' == c || '>' == c)
*/

// 한 문장 끝나는 상황에서만 insert_cmd
// 한 단어 끝나야 list_append_node
// 한 글자씩은 add_char

t_state_shell_parse	shell_parse_space(t_shell_data *p_data, char c)
{
	if (' ' == c || '\t' == c)
		return (S_P_SPACE);
	else if ('\'' == c || '"' == c || '$' == c)
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
	else if ('\'' == c)
		return (S_P_DQUOTE_QUOTE);
	else if ('$' == c)
		return (S_P_DQUOTE_ENV);
	if (shell_parse_node_add_char(p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (S_P_DQUOTE);
}

t_state_shell_parse	shell_parse_env(t_shell_data *p_data, char c)
{
	if (p_data->parse_env->cnt == 0 && (' ' == c || '\t' == c || '?' == c))
		return (treat_first_env(p_data, c));
	else if (' ' == c || '\t' == c || '\'' == c || '"' == c || '$' == c
		|| '(' == c || ')' == c || '&' == c
		|| '|' == c || '<' == c || '>' == c
		|| '-' == c)
	{
		if (shell_parse_find_str_in_env(p_data))
			return (S_P_ERROR);
		if (' ' == c || '\t' == c || '(' == c || ')' == c
			|| '&' == c || '|' == c || '<' == c || '>' == c)
		{
			if (p_data->parse_tmp->cnt)
				if (shell_parse_list_append_node(&p_data->parse_list, \
					&(p_data->parse_tmp)))
					return (S_P_ERROR);
			if (!(' ' == c || '\t' == c))
				if (shell_parse_util_insert_cmd(p_data))
					return (S_P_ERROR);
		}
		return (shell_parse_util_get_state(c));
	}
	if (shell_parse_node_add_char(p_data->parse_env, c))
		return (S_P_ERROR);
	return (S_P_ENV);
}

t_state_shell_parse	shell_parse_open(t_shell_data *p_data, char c)
{
	t_shell_tree_node	*empty;

	empty = tree_new_node(T_EMPTY, NULL, -1, NULL);
	if (NULL == empty)
		return (S_P_ERROR);
	shell_parse_util_push_tree(&p_data->focus, empty);
	if (' ' == c || '\t' == c || '\'' == c || '"' == c || '$' == c
		|| '(' == c || ')' == c
		|| '<' == c || '>' == c)
		return (shell_parse_util_get_state(c));
	else if ('&' == c || '|' == c)
		return (S_P_ERROR);
	if (shell_parse_node_add_char(p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (S_P_STRING);
}
