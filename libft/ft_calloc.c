/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 23:55:41 by alee              #+#    #+#             */
/*   Updated: 2022/03/05 10:32:10 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = (unsigned char *)malloc((sizeof(unsigned char) * count * size));
	if (!ptr)
		return ((void *)(0));
	ft_memset(ptr, 0x00, count * size);
	return (ptr);
}
