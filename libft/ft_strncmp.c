/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 03:34:23 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 21:06:02 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	cur_idx;
	int		ret;

	cur_idx = 0;
	ret = 0;
	while (cur_idx < n)
	{
		if (*((unsigned char *)s1 + cur_idx) != *((unsigned char *)s2 + cur_idx)
			|| *((unsigned char*)s1 + cur_idx) == '\0'
			|| *((unsigned char*)s2 + cur_idx) == '\0')
		{
			ret = *((unsigned char *)s1 + cur_idx) - \
				*((unsigned char *)s2 + cur_idx);
			return (ret);
		}
		cur_idx++;
	}
	return (ret);
}
