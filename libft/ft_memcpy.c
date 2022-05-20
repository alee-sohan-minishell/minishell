/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 00:09:03 by alee              #+#    #+#             */
/*   Updated: 2022/03/05 10:29:24 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	cur_idx;

	if (!dst && !src)
		return ((void *)(0));
	cur_idx = 0;
	while (cur_idx < n)
	{
		*((unsigned char *)dst + cur_idx) = *((unsigned char *)src + cur_idx);
		cur_idx++;
	}
	return (dst);
}
