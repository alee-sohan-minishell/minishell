/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_util_state2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 19:58:14 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/29 19:08:53 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_parse_state.h"
#include "shell_parse_util_state.h"
#include "../libft/libft.h"
#include "shell_parse_util_node_list.h"
#include "shell_parse_util_tree.h"
#include "shell_parse_util_tree2.h"

t_state_shell_parse	treat_first_redirect_env(t_shell_data *p_data, char c)
{
	if (' ' == c || '\t' == c)
	{
		if (shell_parse_node_add_char(p_data->parse_tmp, '$'))
			return (S_P_ERROR);
		if (shell_parse_util_insert_redirect(p_data))
			return (S_P_ERROR);
		p_data->redirect_kind = T_EMPTY;
		return (S_P_REDIRECT_STRING);
	}
	if (add_char_exit_code(p_data))
		return (S_P_ERROR);
	return (get_redirect_state(p_data->redirect_kind));
}

t_state_shell_parse	treat_first_redirect_dquote_env(t_shell_data *p_data,
						char c)
{
	if (' ' == c || '\t' == c || '"' == c || '\'' == c)
	{
		if (shell_parse_node_add_char(p_data->parse_tmp, '$'))
			return (S_P_ERROR);
		if (' ' == c || '\t' == c || '\'' == c)
		{
			if (shell_parse_node_add_char(p_data->parse_tmp, c))
				return (S_P_ERROR);
			return (S_P_REDIRECT_DQUOTE);
		}
		else if ('"' == c)
			return (get_redirect_state(p_data->redirect_kind));
	}
	if (add_char_exit_code(p_data))
		return (S_P_ERROR);
	return (S_P_REDIRECT_DQUOTE);
}

t_state_shell_parse	treat_first_redirect_string_env(t_shell_data *p_data,
						char c)
{
	if (' ' == c || '\t' == c)
	{
		if (shell_parse_node_add_char(p_data->parse_tmp, '$'))
			return (S_P_ERROR);
		if (shell_parse_util_insert_argv_in_cmd(p_data))
			return (S_P_ERROR);
		return (S_P_REDIRECT_STRING);
	}
	if (add_char_exit_code(p_data))
		return (S_P_ERROR);
	return (S_P_REDIRECT_STRING);
}

t_state_shell_parse	treat_first_redirect_string_dquote_env(t_shell_data *p_data,
						char c)
{
	if (' ' == c || '\t' == c || '"' == c)
	{
		if (shell_parse_node_add_char(p_data->parse_tmp, '$'))
			return (S_P_ERROR);
		if (' ' == c || '\t' == c)
		{
			if (shell_parse_node_add_char(p_data->parse_tmp, c))
				return (S_P_ERROR);
			return (S_P_REDIRECT_STRING_DQUOTE);
		}
		else if ('"' == c)
			return (S_P_REDIRECT_STRING);
	}
	if (add_char_exit_code(p_data))
		return (S_P_ERROR);
	return (S_P_REDIRECT_STRING_DQUOTE);
}

char	**append_argv(char **argv, char *arg)
{
	int		cnt;
	char	**new_argv;
	int		i;

	cnt = 0;
	while (argv[cnt++])
		;
	new_argv = malloc(sizeof(char *) * (cnt + 1));
	if (NULL == new_argv)
		return (NULL);
	new_argv[cnt] = NULL;
	i = -1;
	while (argv[++i])
		new_argv[i] = ft_strdup(argv[i]);
	shell_parse_util_argv_free(argv, -1);
	new_argv[i] = arg;
	return (new_argv);
}
