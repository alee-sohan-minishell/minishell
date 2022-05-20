/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 03:05:38 by alee              #+#    #+#             */
/*   Updated: 2022/03/05 10:27:43 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_recursive_n_fd(long long n, int fd)
{
	if (n == 0)
		return ;
	ft_recursive_n_fd(n / 10, fd);
	ft_putchar_fd('0' + (n % 10), fd);
	return ;
}

void	ft_putnbr_fd(int n, int fd)
{
	long long	val;

	val = n;
	if (val == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	else if (val < 0)
	{
		ft_putchar_fd('-', fd);
		val *= (-1);
	}
	ft_recursive_n_fd(val, fd);
	return ;
}
