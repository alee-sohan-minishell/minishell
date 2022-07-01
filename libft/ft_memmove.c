/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan<sohan@student.42seoul.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 02:30:52 by sohan             #+#    #+#             */
/*   Updated: 2022/03/05 10:29:07 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	cur_idx;

	if (!src && !dst)
		return (0);
	cur_idx = 0;
	while (cur_idx < len)
	{
		if (src < dst)
			*((unsigned char *)dst + len - 1 - cur_idx) = \
				*((unsigned char *)src + len - 1 - cur_idx);
		else
			*((unsigned char *)dst + cur_idx) = \
				*((unsigned char *)src + cur_idx);
		cur_idx++;
	}
	return (dst);
}
