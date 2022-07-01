/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan<sohan@student.42seoul.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 23:59:48 by sohan             #+#    #+#             */
/*   Updated: 2022/03/05 10:30:26 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	cur_idx;

	cur_idx = 0;
	while (cur_idx < n)
	{
		if (*((unsigned char *)s + cur_idx) == (unsigned char)c)
			return ((void *)((unsigned char *)s + cur_idx));
		cur_idx++;
	}
	return ((void *)(0));
}
