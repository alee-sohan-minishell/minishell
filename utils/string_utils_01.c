/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 03:50:29 by alee              #+#    #+#             */
/*   Updated: 2022/06/23 21:38:35 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../libft/libft.h"

int	is_variable_rule(char ch)
{
	if (ch == '_')
		return (1);
	if (ft_isalpha(ch))
		return (1);
	return (0);
}

void	ft_strcat_buf(char *buf, int buf_len, const char *pre_cmd, \
	const char *param)
{
	if (pre_cmd)
	{
		ft_strlcat(buf, pre_cmd, buf_len);
		ft_strlcat(buf, ": ", buf_len);
	}
	if (param)
	{
		ft_strlcat(buf, param, buf_len);
		ft_strlcat(buf, ": ", buf_len);
	}
	return ;
}
