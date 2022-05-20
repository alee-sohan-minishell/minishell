/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 03:16:34 by alee              #+#    #+#             */
/*   Updated: 2022/03/05 10:30:47 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	cur_idx;

	cur_idx = 0;
	while (cur_idx < n)
	{
		*((unsigned char *)dst + cur_idx) = *((unsigned char *)src + cur_idx);
		if (*((unsigned char *)src + cur_idx) == (unsigned char)c)
			return ((void *)(unsigned char *)dst + cur_idx + 1);
		cur_idx++;
	}
	return ((void *)(0));
}
