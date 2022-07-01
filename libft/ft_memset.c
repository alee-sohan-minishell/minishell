/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan<sohan@student.42seoul.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 23:47:23 by sohan             #+#    #+#             */
/*   Updated: 2022/03/05 10:28:17 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	cur_idx;

	cur_idx = 0;
	while (cur_idx < len)
	{
		*((unsigned char *)b + cur_idx) = (unsigned char)c;
		cur_idx++;
	}
	return (b);
}
