/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:08:02 by alee              #+#    #+#             */
/*   Updated: 2022/06/17 22:31:56 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../shell/shell.h"
#include "../utils/state_machine_utils_01.h"
#include "../utils/error_msg_utils_01.h"
#include "../parse/shell_parse_state.h"
#include "../parse/shell_parse_utils1.h"
#include "../parse/shell_parse_utils3.h"
#include "../tree/shell_tree.h"
#include "../tree/shell_heredoc.h"
#include "../parse/shell_parse_check_tree.h"

void	shell_parse_free(t_shell_data *p_data)
{
	t_parse_node	*node;
	t_parse_node	*tmp;

	node = p_data->parse_list.head.next;
	while (node)
	{
		tmp = node;
		node = node->next;
		if (tmp->str)
			free(tmp->str);
		free(tmp);
	}
	p_data->parse_list.head.next = NULL;
	shell_parse_delete_node(&p_data->parse_env);
	shell_parse_delete_node(&p_data->parse_redirect);
	tree_delete(&p_data->tree);
	heredoc_delete(&p_data->heredoc);
}

int	shell_parse_check(t_shell_data *p_data, t_state_shell_parse state)
{
	if (S_P_SPACE == state || S_P_STRING == state)
	{
		if (p_data->parse_list.tail->cnt)
			if (NULL == shell_parse_util_append_new_node(&p_data->parse_list))
				return (-1);
	}
	else if (S_P_QUOTE == state || S_P_DQUOTE == state
		|| S_P_OPEN == state || S_P_AND == state || S_P_PIPE == state
		|| S_P_REDIRECT_IN == state || S_P_REDIRECT_OUT == state
		|| S_P_BOOL_AND == state || S_P_BOOL_OR == state
		|| is_redirect(state) || S_P_DQUOTE_ENV == state)
		return (-1);
	else if (S_P_ENV == state)
	{
		if (shell_parse_util_env_convert(p_data))
			return (-1);
		if (NULL == shell_parse_util_append_new_node(&p_data->parse_list))
			return (-1);
	}
	if (p_data->parse_list.head.next)
		if (shell_parse_util_insert_cmd(p_data))
			return (-1);
	return (0);
}

int	loop_parse(t_shell_data *p_data, t_state_shell_parse *state, char *str)
{
	while (*str)
	{
		if (S_P_ERROR == *state)
		{
			ft_perror_param("error while parse", str, 0); // TODO 뒷 문장 전체 출력하는 걸로 괜찮은가?
			return (-1);
		}
		else if (S_P_SPACE == *state || S_P_QUOTE == *state
			|| S_P_DQUOTE == *state || S_P_ENV == *state
			|| S_P_DQUOTE_ENV == *state)
			*state = shell_parse_state1(state, p_data, *str);
		else if (S_P_OPEN == *state || S_P_CLOSE == *state
			|| S_P_REDIRECT_SPACE == *state)
			*state = shell_parse_state2(state, p_data, *str);
		else if (S_P_AND == *state || S_P_PIPE == *state
			|| S_P_REDIRECT_IN == *state || S_P_REDIRECT_OUT == *state)
			*state = shell_parse_state3(state, p_data, *str);
		else if (S_P_BOOL_AND == *state || S_P_BOOL_OR == *state
			|| S_P_REDIRECT_HEREDOC == *state || S_P_REDIRECT_APPEND == *state
			|| S_P_STRING == *state)
			*state = shell_parse_state4(state, p_data, *str);
		++str;
	}
	return (0);
}

// \ 이 중간에 포함 되거나, ' " 개수가 홀 수 일 때 parse 안 함
int	shell_parse_check_not_interpret(char *str)
{
	int	cnt_q;
	int	cnt_dq;

	cnt_q = 0;
	cnt_dq = 0;
	while (*str)
	{
		if ('\\' == *str)
			return (-1);
		else if ('\'' == *str)
			++cnt_q;
		else if ('"' == *str)
			++cnt_dq;
		++str;
	}
	return (cnt_q || cnt_dq);
}

void	shell_parse(t_shell_data *p_data)
{
	t_state_shell_parse	state;

	if (!p_data->line || shell_parse_check_not_interpret(p_data->line))
	{
		ft_set_status(p_data, S_ERROR);
		return ;
	}
	state = S_P_SPACE;
	if (loop_parse(p_data, &state, p_data->line)
		&& shell_parse_check(p_data, state) && shell_parse_check_tree(p_data))
	{
		shell_parse_free(p_data);
		ft_set_status(p_data, S_ERROR);
		return ;
	}
	ft_set_status(p_data, S_CMD);
	return ;
}
