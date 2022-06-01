/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_state1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:34:57 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/11 22:46:03 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../shell/shell.h"
#include "shell_parse_state.h"
#include "shell_parse_utils1.h"
#include "shell_parse_utils2.h"
#include "../env/env_list.h"
#include "../env/env_list_interface_01.h"
#include "../utils/error_msg_utils_01.h"

t_state_shell_parse	shell_parse_space(t_shell_data *p_data, char *s)
{
	t_state_shell_parse	next_state;

	next_state = shell_parse_util_strcmp(S_P_SPACE, s);
	if (S_P_STRING == next_state)
	{
		if (shell_parse_util_add_char(&p_data->parse_list, *s))
			return (S_P_ERROR);
	}
	else if (NULL != p_data->parse_list.tail
		&& shell_parse_util_is_cmd_end(next_state))
		//# 1. utils2에 있는 is end 함수는 지워야 할듯
		// 쓸 줄 알고 만들었는데 사이에 스페이스 없으면 문자취급이고
		// 스페이스 있으면 그 상태로 넘어가야 함, 조건이 조금 다름
		// echo~랑 echo ~랑 돌려보셈
	else if (!(S_P_ENV == next || S_P_SHARP == next || S_P_TILDA == next
		|| S_P_DASH == next || S_P_DQUOTE == next || S_P_DQUOTE_ENV == next
		|| S_P_ENV == next || S_P_QUOTE == next || S_P_STRING == next))

		if (shell_parse_util_insert_cmd(p_data))
			return (S_P_ERROR);
	return (next_state);
}

t_state_shell_parse	shell_parse_quote(t_shell_data *p_data, char *s)
{
	t_state_shell_parse	next_state;
	t_parse_node		*node;

	next_state = shell_parse_util_strcmp(S_P_QUOTE, s);
	if (S_P_QUOTE == next_state)
	{
		node = shell_parse_util_append_new_node(&p_data->parse_list);
		if (NULL == node)
			return (S_P_ERROR);
		return (S_P_SPACE);
	}
	if (shell_parse_util_add_char(&p_data->parse_list, *s))
		return (S_P_ERROR);
	return (S_P_QUOTE);
}

t_state_shell_parse	shell_parse_dquote(t_shell_data *p_data, char *s)
{
	if (S_P_DQUOTE_ENV == shell_parse_util_strcmp(S_P_DQUOTE, s))
		return (S_P_DQUOTE_ENV);
	if (shell_parse_util_add_char(&p_data->parse_list, *s))
		return (S_P_ERROR);
	return (S_P_DQUOTE);
}

t_state_shell_parse	shell_parse_env(t_shell_data *p_data, char *s)
{
	t_state_shell_parse	next_state;
	t_env_node			*env_node;
	char				*key;
	int					cnt;

	next_state = shell_parse_util_strcmp(S_P_ENV, s);
	if (S_P_STRING != next_state)
	{
		key = shell_parse_util_env_to_str(&p_data->parse_env);
		if (NULL == key)
			return (S_P_ERROR);
		if (env_node_search(&p_data->env_list, key, &env_node) == 0)
		{
			ft_perror_param("env", key, 0);
			free(key);
			return (S_P_ERROR);
		}
		cnt = -1;
		while (env_node->value[++cnt])
			shell_parse_util_add_char(&p_data->parse_list, env_node->value[cnt]);
		return (next_state);
	}
	// TODO env 다음 state로 오면 안되는 경우가 있는지 생각해봐야 함
	if (shell_parse_util_env_add_char(&p_data->parse_env, *s))
		return (S_P_ERROR);
	return (S_P_ENV);
}

// 위에꺼는 next_state로 넘어가는데 이거는 dquote로 넘어가야 함
t_state_shell_parse	shell_parse_dquote_env(t_shell_data *p_data, char *s)
{
	// TODO
	t_env_node			*env_node;
	char				*key;
	int					cnt;

	if (S_P_STRING != shell_parse_util_strcmp(S_P_DQUOTE_ENV, s))
	{
		key = shell_parse_util_env_to_str(&p_data->parse_env);
		if (NULL == key)
			return (S_P_ERROR);
		if (env_node_search(&p_data->env_list, key, &env_node) == 0)
		{
			ft_perror_param("env", key, 0);
			free(key);
			return (S_P_ERROR);
		}
		cnt = -1;
		while (env_node->value[++cnt])
			shell_parse_util_add_char(&p_data->parse_list, env_node->value[cnt]);
		return (S_P_DQUOTE);
	}
	if (shell_parse_util_env_add_char(&p_data->parse_env, *s))
		return (S_P_ERROR);
	return (S_P_ENV);
}
