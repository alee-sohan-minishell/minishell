/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 01:22:07 by alee              #+#    #+#             */
/*   Updated: 2022/03/05 10:31:44 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' || \
		c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	size_t		cur_idx;
	int			sign;
	long long	ret;

	cur_idx = 0;
	sign = 1;
	ret = 0;
	while (ft_isspace(*(str + cur_idx)))
		cur_idx++;
	if (*(str + cur_idx) == '-' || *(str + cur_idx) == '+')
	{
		if (*(str + cur_idx) == '-')
			sign = -1;
		cur_idx++;
	}
	while (ft_isdigit(*(str + cur_idx)))
	{
		ret *= 10;
		ret += *(str + cur_idx) - '0';
		cur_idx++;
	}
	return (ret * sign);
}
