/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_util_state.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:40:49 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/24 23:17:26 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_parse_state.h"

t_state_shell_parse	shell_parse_util_get_state(char c)
{
	int			cnt;
	const char	str[] = {' ', '\'', '"', '$',
		'(', ')', '&', '|', '<', '>'};

	cnt = -1;
	while (++cnt < 10) // 10개 중에 매칭되는 상태 리턴
		if (str[cnt] == c)
			return (cnt);
	return (S_P_STRING); // 그게 아니면 string임
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
