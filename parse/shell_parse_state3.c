/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_state3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:34:57 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/17 23:57:31 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "shell_parse_state.h"
#include "../tree/shell_tree.h"
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

	if ('|' == c)
		return (S_P_BOOL_OR);
	pipe = tree_new_node(T_PIPE, NULL, 0, NULL);
	if (NULL == pipe)
		return (S_P_ERROR);
	tree_insert(&p_data->focus, pipe);
	if (' ' == c || '\'' == c || '"' == c || '$' == c || '<' == c || '>' == c)
		return (shell_parse_util_get_state(c));
	else if ('#' == c || '-' == c || '~' == c || ')' == c || '&' == c)
		return (S_P_ERROR);
	if (shell_parse_util_add_char(&p_data->parse_list, c))
		return (S_P_ERROR);
	return (S_P_STRING);
}

t_state_shell_parse	shell_parse_redirect_in(t_shell_data *p_data, char c)
{
	// TODO
	//# TODO 리다이렉트인 경우 포커스가 밀려나는게 아니라 자식을 밀어냄
	//# TODO 커맨드가 아니면 포커스는 넣은 것
}

t_state_shell_parse	shell_parse_redirect_out(t_shell_data *p_data, char c)
{
	// TODO
}

t_state_shell_parse	shell_parse_finsih(t_shell_data *p_data, char c)
{
	// TODO
}
