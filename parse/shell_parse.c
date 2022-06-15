/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:08:02 by alee              #+#    #+#             */
/*   Updated: 2022/06/05 17:00:21 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "../utils/state_machine_utils_01.h"
#include "../parse/shell_parse_state.h"

void	shell_parse_error()
{
	// TODO tree_node free 처리 해야 함
}

void	shell_parse_check()
{
	// TODO: str이 \0여서 while문 안 돌아서 if else에서 처리 안되는 경우 체크해야 함
	// string으로 끝난 경우 append_new_node, inset_cmd
}

void	loop_parse(t_shell_data *p_data, t_state_shell_parse *state, char *str)
{
	while (*str)
	{
		if (S_P_ERROR == *state)
		{
			shell_parse_error(); // TODO
			break ;
		}
		else if (S_P_SPACE == *state || S_P_QUOTE == *state
			|| S_P_DQUOTE == *state || S_P_ENV == *state
			|| S_P_DQUOTE_ENV == *state)
			*state = shell_parse_state1(state, p_data, *str);
		else if (S_P_SHARP == *state || S_P_DASH == *state
			|| S_P_TILDA == *state || S_P_OPEN == *state || S_P_CLOSE == *state)
			*state = shell_parse_state2(state, p_data, *str);
		else if (S_P_AND == *state || S_P_PIPE == *state || S_P_FINISH == *state
			|| S_P_REDIRECT_IN == *state || S_P_REDIRECT_OUT == *state)
			*state = shell_parse_state3(state, p_data, *str);
		else if (S_P_BOOL_AND == *state || S_P_BOOL_OR == *state
			|| S_P_REDIRECT_HEREDOC == *state || S_P_REDIRECT_APPEND == *state
			|| S_P_STRING == *state)
			*state = shell_parse_state4(state, p_data, *str);
		++str;
	}
}

void	shell_parse(t_shell_data *p_data)
{
	t_state_shell_parse	state;
	char				*str;

	if (!p_data->line)
	{
		ft_set_status(p_data, S_ERROR);
		return ;
	}
	str = p_data->line;
	state = S_P_SPACE;
	loop_parse(p_data, &state, str);
	shell_parse_check(); // TODO
	// TODO malloc 해준 임시 parse 임시 변수들 free 해줬는지 체크하기
	ft_set_status(p_data, S_CMD);
	return ;
}
