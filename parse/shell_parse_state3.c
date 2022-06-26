/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_state3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:34:57 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/26 15:44:38 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "shell_parse_state.h"
#include "shell_parse_util_state.h"
#include "../tree_heredoc/shell_tree.h"
#include "../parse/shell_parse_util_tree.h"
#include "shell_parse_util_node_list.h"

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

	//TODO 나중에 pnum 지우기
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
	else if ('|' == c)
		return (S_P_BOOL_OR);
	if (shell_parse_node_add_char(p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (S_P_STRING);
}

t_state_shell_parse	shell_parse_redirect_in(t_shell_data *p_data, char c)
{
	// 임시 node에 add_char 하다가 list로 넣을지, redirect tree_insert 할지 결정하자
	p_data->redirect_kind = T_REDIRECT_IN;
	if (p_data->parse_tmp->cnt == 0 && (' ' == c || '\t' == c)) // 아무것도 없이 처음에 ' ' 만났을 때만, 아닌 경우는 문자 추가하러 가야 됨
		return (S_P_REDIRECT_IN);
	else if (' ' == c || '\t' == c || '(' == c || ')' == c
		|| '&' == c || '|' == c || '>' == c)
	{
		if (shell_parse_util_insert_redirect(p_data))
			return (S_P_ERROR);
		p_data->redirect_kind = T_EMPTY;
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
