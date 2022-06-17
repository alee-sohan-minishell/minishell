/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_state4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:34:57 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/18 06:30:06 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "shell_parse_state.h"
#include "shell_parse_utils1.h"
#include "shell_parse_utils2.h"
#include "../tree/shell_tree.h"
#include "../tree/shell_tree_utils.h"

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
	// TODO
}

t_state_shell_parse	shell_parse_redirect_append(t_shell_data *p_data, char c)
{
	// TODO
}

t_state_shell_parse	shell_parse_string(t_shell_data *p_data, char c)
{
	if (' ' == c)
	{
		if (NULL == shell_parse_util_append_new_node(&p_data->parse_list))
			return (S_P_ERROR);
		return (S_P_SPACE);
	}
	else if ('\'' == c || '"' == c || '$' == c)
		return (shell_parse_util_get_state(c));
	else if ('(' == c || ')' == c || '&' == c
		|| '|' == c || '<' == c || '>' == c)
	{
		if (shell_parse_util_insert_cmd(p_data)) //# 2.TODO cat< cat < 공백 나오는 경우랑 공백 없이 바로 다음 문자 나오는 경우, append node 안해서 insert_cmd 버그 안나나?
			return (S_P_ERROR);
		return (shell_parse_util_get_state(c));
	}
	if (shell_parse_util_add_char(&p_data->parse_list, c))
		return (S_P_ERROR);
	return (S_P_STRING);
}
