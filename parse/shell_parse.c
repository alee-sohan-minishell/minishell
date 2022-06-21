/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:08:02 by alee              #+#    #+#             */
/*   Updated: 2022/06/21 16:01:21 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "../tree_heredoc/shell_tree.h"
#include "../tree_heredoc/shell_heredoc.h"
#include "shell_parse_node_list.h"
#include "shell_parse_state.h"
#include "shell_parse_check_tree.h"
#include "../utils/error_msg_utils_01.h"
#include "../utils/state_machine_utils_01.h"
#include "shell_parse_util_node_list.h"
#include "shell_parse_util_tree.h"

void	shell_parse_free(t_shell_data *p_data)
{
	tree_free(&p_data->tree);
	p_data->focus = &p_data->tree;
	heredoc_list_free(&p_data->heredoc_list);
	shell_parse_list_free(&p_data->parse_list);
	shell_parse_node_free(p_data->parse_tmp);
	shell_parse_node_free(p_data->parse_env);
}

int	shell_parse_check(t_shell_data *p_data, t_state_shell_parse state)
{
	if (S_P_QUOTE == state || S_P_DQUOTE == state
		|| S_P_OPEN == state || S_P_AND == state || S_P_PIPE == state
		|| S_P_BOOL_AND == state || S_P_BOOL_OR == state)
		return (-1);
	if (p_data->parse_env->cnt) // 아직 남아 있는게 있으면
	{
		if (shell_parse_find_str_in_env(p_data)) // p_data->parse_env에 있는 문자 key로 env 찾아서 p_data->parse_tmp에 바로 add_char 함
			return (S_P_ERROR);
	}
	if (shell_parse_util_is_redirect(state))
	{
		if (p_data->parse_tmp->cnt == 0)
			return (-1);
		if (shell_parse_util_insert_redirect(p_data))
			return (-1);
	}
	if (p_data->parse_tmp->cnt)
	{
		if (shell_parse_list_append_node(&p_data->parse_list, &(p_data->parse_tmp)))
			return (-1);
	}
	if (p_data->parse_list.cnt)
		if (shell_parse_util_insert_cmd(p_data))
			return (-1);
	return (0);
}

char	*loop_parse(t_shell_data *p_data, t_state_shell_parse *state, char *str)
{
	while (*str)
	{
		if (S_P_ERROR == *state)
			return (str);
		else if (S_P_SPACE == *state || S_P_QUOTE == *state
			|| S_P_DQUOTE == *state || S_P_ENV == *state
			|| S_P_DQUOTE_ENV == *state)
			*state = shell_parse_state1(*state, p_data, *str);
		else if (S_P_OPEN == *state || S_P_CLOSE == *state)
			*state = shell_parse_state2(*state, p_data, *str);
		else if (S_P_AND == *state || S_P_PIPE == *state
			|| S_P_REDIRECT_IN == *state || S_P_REDIRECT_OUT == *state)
			*state = shell_parse_state3(*state, p_data, *str);
		else if (S_P_BOOL_AND == *state || S_P_BOOL_OR == *state
			|| S_P_REDIRECT_HEREDOC == *state || S_P_REDIRECT_APPEND == *state
			|| S_P_STRING == *state)
			*state = shell_parse_state4(*state, p_data, *str);
		else if (S_P_REDIRECT_ENV == *state || S_P_REDIRECT_QUOTE == *state
			|| S_P_REDIRECT_DQUOTE == *state
			|| S_P_REDIRECT_DQUOTE_ENV == *state)
			*state = shell_parse_state5(*state, p_data, *str);
		++str;
	}
	return (NULL);
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
	char				*ret;

	if (!p_data->line || shell_parse_check_not_interpret(p_data->line))
	{
		ft_set_status(p_data, S_ERROR);
		return ;
	}
	state = S_P_SPACE;
	ret = loop_parse(p_data, &state, p_data->line);
	if (ret && shell_parse_check(p_data, state)
		&& shell_parse_check_tree(p_data->focus))
	{
		ft_perror_param("error while parse", ret, 0); // TODO 뒷 문장 전체 출력하는 걸로 괜찮은가?
		shell_parse_free(p_data);
		ft_set_status(p_data, S_ERROR);
		return ;
	}
	ft_set_status(p_data, S_CMD); // TODO 바로 CMD로 넘어가기 때문에 CMD에서 shell_parse_free() 호출해줘야 함
	return ;
}
