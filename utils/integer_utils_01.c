/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer_utils_01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 04:07:03 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 04:08:01 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

int	is_valid_num(char *str)
{
	int	idx;

	if (!str)
		return (0);
	idx = 0;
	if (str[idx] == '+' || str[idx] == '-')
		idx++;
	while (str[idx])
	{
		if (ft_isdigit(str[idx]) == 0)
			return (0);
		idx++;
	}
	return (1);
}

int	ft_atol(char *str, long long *o_var)
{
	long long	ret;
	int			idx;
	int			sign;

	ret = 0;
	idx = 0;
	sign = 1;
	if (str[idx] == '-' || str[idx] == '+')
	{
		if (str[idx] == '-')
			sign = -1;
		idx++;
	}
	while (ft_isdigit(str[idx]))
	{
		ret *= 10;
		ret += str[idx++] - '0';
	}
	*o_var = ret * sign;
	if ((sign == 1 && ret < 0) || (sign == -1 && ret * sign > 0))
		return (0);
	return (1);
}
