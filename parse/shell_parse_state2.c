/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_state2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:34:57 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/05 16:46:21 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "shell_parse_state.h"

#include "../tree/shell_tree.h"
#include "shell_parse_utils1.h"

// string state에서 이쪽으로 넘어오진 않음 공백 없고 바로 다른 문자랑 붙은 경우 string 취급됨
t_state_shell_parse	shell_parse_sharp(t_shell_data *p_data, char c)
{
	return (S_P_FINISH);
}

// string state에서 이쪽으로 넘어오진 않음 공백 없고 바로 다른 문자랑 붙은 경우 string 취급됨
t_state_shell_parse	shell_parse_dash(t_shell_data *p_data, char c)
{
	// TODO //# 1.
}

// string state에서 이쪽으로 넘어오진 않음 공백 없고 바로 다른 문자랑 붙은 경우 string 취급됨
t_state_shell_parse	shell_parse_tilda(t_shell_data *p_data, char c)
{
	// TODO
}

t_state_shell_parse	shell_parse_open(t_shell_data *p_data, char c)
{
	t_shell_tree_node	*empty;

	empty = tree_new_node(T_EMPTY, NULL, 0, NULL);
	if (NULL == empty)
		return (S_P_ERROR);
	tree_insert(&p_data->focus, empty);
	if (' ' == c || '\'' == c || '"' == c || '$' == c || '-' == c
		|| '~' == c || '(' == c || ')' == c || '<' == c || '>' == c)
		return (shell_parse_util_get_state(c));
	else if ('#' == c || '&' == c || '|' == c) // # 도 원래 정상 동작하긴 함 한 여러 줄 걸친 괄호가 과제 요구사항 아니라서 에러 처리
		return (S_P_ERROR);
	if (shell_parse_util_add_char(&p_data->parse_list, c))
		return (S_P_ERROR);
	return (S_P_STRING);
}

t_state_shell_parse	shell_parse_close(t_shell_data *p_data, char c)
{
	p_data->focus = p_data->focus->parent;
	if (' ' == c || '\'' == c || '"' == c || '$' == c || '#' == c || '(' == c
		|| ')' == c || '&' == c || '|' == c || '<' == c || '>' == c)
		return (shell_parse_util_get_state(c));
	else if ('-' == c || '~' == c)
		return (S_P_ERROR);
	if (shell_parse_util_add_char(&p_data->parse_list, c))
		return (S_P_ERROR);
	return (S_P_STRING);
}
