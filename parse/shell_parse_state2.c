/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_state2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:34:57 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/20 23:59:51 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//# -1. 여기서 부터 아래 새로 만든 함수들로 쭉 봐야함
#include "../shell/shell.h"
#include "shell_parse_state.h"
#include "../tree_heredoc/shell_tree.h"
#include "../tree_heredoc/shell_tree_utils.h"
#include "shell_parse_utils1.h"

t_state_shell_parse	shell_parse_open(t_shell_data *p_data, char c)
{
	t_shell_tree_node	*empty;

	if (' ' == c || '\'' == c || '"' == c || '$' == c
		|| '(' == c || ')' == c
		|| '<' == c || '>' == c)
	{
		empty = tree_new_node(T_EMPTY, NULL, 0, NULL);
		shell_tree_push(&p_data->focus, empty);
		if (NULL == empty)
			return (S_P_ERROR);
		return (shell_parse_util_get_state(c));
	}
	else if ('&' == c || '|' == c)
		return (S_P_ERROR);
	empty = tree_new_node(T_EMPTY, NULL, 0, NULL);
	if (NULL == empty)
		return (S_P_ERROR);
	shell_tree_push(&p_data->focus, empty);
	if (shell_parse_util_add_char(&p_data->parse_list, c))
		return (S_P_ERROR);
	return (S_P_STRING);
}

t_state_shell_parse	shell_parse_close(t_shell_data *p_data, char c)
{
	if (p_data->focus->parent)
		p_data->focus = p_data->focus->parent;
	if (' ' == c || '\'' == c || '"' == c || '$' == c
		|| '(' == c || ')' == c || '&' == c
		|| '|' == c || '<' == c || '>' == c)
		return (shell_parse_util_get_state(c));
	if (shell_parse_util_add_char(&p_data->parse_list, c))
		return (S_P_ERROR);
	return (S_P_STRING);
}

t_state_shell_parse	shell_parse_redirect_space(t_shell_data *p_data, char c)
{
	// TODO //# 이거 그냥 redirect_in 복사해 온 거
	// TODO 리다이렉트인 경우 포커스가 밀려나는게 아니라 자식을 밀어냄
	// TODO 커맨드가 아니면 포커스는 넣은 것

	if (' ' == c || '\'' == c || '"' == c || '$' == c
		|| '(' == c || ')' == c || '&' == c
		|| '|' == c || '<' == c || '>' == c)

	if (' ' == c || '\'' == c || '"' == c || '$' == c)
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

//# < t1 cat TODO redirect string 하나 더 만드는게 나을 듯
