/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 07:59:35 by alee              #+#    #+#             */
/*   Updated: 2022/03/05 10:21:47 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	null_idx;
	size_t	cur_idx;
	size_t	src_len;
	size_t	dst_len;

	null_idx = 0;
	cur_idx = 0;
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dst_len >= dstsize)
		return (dstsize + src_len);
	while (*(dst + null_idx) != '\0')
		null_idx++;
	while (cur_idx < dstsize - 1 - dst_len)
	{
		if (*((char *)src + cur_idx) == '\0')
			break ;
		*(dst + null_idx + cur_idx) = *((char *)src + cur_idx);
		cur_idx++;
	}
	*(dst + null_idx + cur_idx) = '\0';
	return (dst_len + src_len);
}
