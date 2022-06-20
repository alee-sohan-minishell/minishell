/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_state3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:34:57 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/20 19:43:26 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "shell_parse_state.h"
#include "../tree_heredoc/shell_tree.h"
#include "../tree_heredoc/shell_tree_utils.h"
#include "shell_parse_utils1.h"

t_state_shell_parse	shell_parse_and(t_shell_data *p_data, char c)
{
	if ('&' == c)
		return (S_P_BOOL_AND);
	return (S_P_ERROR);
}

t_state_shell_parse	shell_parse_pipe(t_shell_data *p_data, char c)
{
	t_shell_tree_node	*pipe;

	if (' ' == c || '\'' == c || '"' == c || '$' == c
		|| '(' == c || '<' == c || '>' == c)
	{
		pipe = tree_new_node(T_PIPE, NULL, 0, NULL);
		if (NULL == pipe)
			return (S_P_ERROR);
		shell_tree_push(&p_data->focus, pipe);
		return (shell_parse_util_get_state(c));
	}
	else if (')' == c || '&' == c)
		return (S_P_ERROR);
	else if ('|' == c)
		return (S_P_BOOL_OR);
	if (shell_parse_util_add_char(&p_data->parse_list, c))
		return (S_P_ERROR);
	return (S_P_STRING);
}

t_state_shell_parse	shell_parse_redirect_in(t_shell_data *p_data, char c)
{
	// TODO
	//# TODO 리다이렉트인 경우 포커스가 밀려나는게 아니라 자식을 밀어냄
	//# TODO 커맨드가 아니면 포커스는 넣은 것

	p_data->redirect_flag = 1; //# 1.플래그 하지말고, env나 quote를 위해서 임시 node에 add_char 하다가 list로 넣을지, redirect tree_insert 할지 결정하자
	// tmp_append_to_list랑, add_char_tmp 만들면 될 듯
	if (' ' == c)
		return (S_P_REDIRECT_SPACE);
	else if ('\'' == c || '"' == c || '$' == c)
		return (shell_parse_util_get_state(c));
	else if ('<' == c)
		return (S_P_REDIRECT_HEREDOC);
	else if ('(' == c || ')' == c || '&' == c || '|' == c || '>' == c)
		return (S_P_ERROR);
	if (shell_parse_util_add_char(&p_data->parse_list, c))
		return (S_P_ERROR);
	return (S_P_REDIRECT_IN);
}

t_state_shell_parse	shell_parse_redirect_out(t_shell_data *p_data, char c)
{
	// TODO
}
