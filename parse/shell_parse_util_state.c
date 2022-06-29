/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_util_state.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:40:49 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/28 22:08:55 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../shell/shell.h"
#include "shell_parse_state.h"
#include "shell_parse_util_node_list.h"
#include "../libft/libft.h"
#include "shell_parse_state.h"
#include "shell_parse_util_tree.h"
#include "shell_parse_util_tree2.h"

t_state_shell_parse	shell_parse_util_get_state(char c)
{
	int			cnt;
	const char	str[] = {' ', '\'', '"', '$',
		'(', ')', '&', '|', '<', '>'};

	cnt = -1;
	while (++cnt < 10)
		if (str[cnt] == c)
			return (cnt);
	return (S_P_STRING);
}

int	is_redirect_state(t_state_shell_parse state)
{
	if (S_P_REDIRECT_IN == state || S_P_REDIRECT_OUT == state
		|| S_P_REDIRECT_HEREDOC == state || S_P_REDIRECT_APPEND == state
		|| S_P_REDIRECT_ENV == state || S_P_REDIRECT_QUOTE == state
		|| S_P_REDIRECT_DQUOTE == state || S_P_REDIRECT_DQUOTE_ENV == state)
		return (1);
	return (0);
}

int	add_char_exit_code(t_shell_data *p_data)
{
	char	*str;
	int		cnt;

	str = ft_itoa(g_exit_code);
	if (NULL == str)
		return (-1);
	cnt = -1;
	while (str[++cnt])
	{
		if (shell_parse_node_add_char(p_data->parse_tmp, str[cnt]))
		{
			free(str);
			return (-1);
		}
	}
	free(str);
	return (0);
}

t_state_shell_parse	treat_first_env(t_shell_data *p_data, char c)
{
	if (' ' == c || '\t' == c || '\'' == c)
	{
		if (shell_parse_node_add_char(p_data->parse_tmp, '$'))
			return (S_P_ERROR);
		if (shell_parse_list_append_node(\
			&p_data->parse_list, &(p_data->parse_tmp)))
			return (S_P_ERROR);
		if ('\'' == c)
			return (S_P_QUOTE);
		return (S_P_SPACE);
	}
	else if ('?' == c)
	{
		if (add_char_exit_code(p_data))
			return (S_P_ERROR);
	}
	return (S_P_STRING);
}

t_state_shell_parse	treat_first_dquote_env(t_shell_data *p_data, char c)
{
	if (' ' == c || '\t' == c || '"' == c || '\'' == c)
	{
		if (shell_parse_node_add_char(p_data->parse_tmp, '$'))
			return (S_P_ERROR);
		if (' ' == c || '\t' == c || '\'' == c)
		{
			if (shell_parse_node_add_char(p_data->parse_tmp, c))
				return (S_P_ERROR);
			return (S_P_DQUOTE);
		}
		else if ('"' == c)
			return (S_P_STRING);
	}
	else if ('?' == c)
	{
		if (add_char_exit_code(p_data))
			return (S_P_ERROR);
	}
	return (S_P_DQUOTE);
}
