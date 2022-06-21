/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_util_state.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:40:49 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/20 21:57:04 by min-jo           ###   ########.fr       */
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
