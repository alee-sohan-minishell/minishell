/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan<sohan@student.42seoul.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 23:55:41 by sohan             #+#    #+#             */
/*   Updated: 2022/03/05 10:32:10 by sohan            ###   ########.fr       */
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
