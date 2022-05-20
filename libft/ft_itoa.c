/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 22:54:33 by alee              #+#    #+#             */
/*   Updated: 2022/03/05 10:41:20 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_n_len(int n, int *sign)
{
	int	len;

	len = 0;
	*sign = 1;
	if (n < 0)
	{
		len++;
		*sign = -1;
	}
	while (1)
	{
		if (n == 0)
			break ;
		len++;
		n /= 10;
	}
	return (len);
}

static void	ft_recur_digit(int n, char *buf, int *idx)
{
	if (n == 0)
		return ;
	ft_recur_digit(n / 10, buf, idx);
	buf[(*idx)++] = '0' + (n % 10);
	return ;
}

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	int		idx;

	if (n == 0)
		return (ft_strdup("0"));
	else if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = (char *)malloc(ft_n_len(n, &sign) + 1);
	if (str == (char *)(0))
		return ((char *)(0));
	idx = 0;
	if (sign != 1)
	{
		str[idx++] = '-';
		n *= -1;
	}
	ft_recur_digit(n, str, &idx);
	str[idx] = '\0';
	return (str);
}
