/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 01:37:06 by alee              #+#    #+#             */
/*   Updated: 2022/03/05 10:21:30 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	ret;
	size_t	cur_idx;

	if (!src)
		return (0);
	cur_idx = 0;
	ret = ft_strlen(src);
	if (dstsize == 0)
		return (ret);
	while (cur_idx < dstsize - 1)
	{
		if (*((char *)src + cur_idx) == '\0')
			break ;
		*(dst + cur_idx) = *((char *)src + cur_idx);
		cur_idx++;
	}
	*(dst + cur_idx) = '\0';
	return (ret);
}
