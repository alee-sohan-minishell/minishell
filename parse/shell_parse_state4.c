/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_state4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:34:57 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/05 16:46:54 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "shell_parse_state.h"
#include "shell_parse_utils1.h"
#include "shell_parse_utils2.h"
#include "shell_parse_utils3.h"
#include "../tree/shell_tree.h"
#include "../tree/shell_tree_utils.h"

t_state_shell_parse	shell_parse_bool_and(t_shell_data *p_data, char *s)
{
	// TODO
}

t_state_shell_parse	shell_parse_bool_or(t_shell_data *p_data, char *s)
{
	// TODO
}

t_state_shell_parse	shell_parse_redirect_heredoc(t_shell_data *p_data, char *s)
{
	// TODO
}

t_state_shell_parse	shell_parse_redirect_append(t_shell_data *p_data, char *s)
{
	// TODO
}

t_state_shell_parse	shell_parse_string(t_shell_data *p_data, char *s)
{
	t_state_shell_parse	next;
	t_parse_node		*parse_node;

	next = shell_parse_util_strcmp(S_P_STRING, s);
	if (S_P_STRING == next)
		if (shell_parse_util_add_char(&p_data->parse_list, *s))
			return (S_P_ERROR);
	else if (S_P_SPACE == next)
	{
		parse_node = shell_parse_util_append_new_node(&p_data->parse_list);
		if (NULL == parse_node)
			return (S_P_ERROR);
	}
	else if (!(S_P_ENV == next || S_P_SHARP == next || S_P_TILDA == next
		|| S_P_DASH == next || S_P_DQUOTE == next || S_P_DQUOTE_ENV == next
		|| S_P_ENV == next || S_P_QUOTE == next || S_P_STRING == next))
		if (shell_parse_util_insert_cmd(p_data))
			return (S_P_ERROR);
	// string 다음에 tilda, dash, env, sharp 나오면 string 취급됨, 다음 2개 돌려보셈
	// echo test~
	// ehoc test ~
	return (next);
}
