/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 00:29:55 by alee              #+#    #+#             */
/*   Updated: 2022/03/05 10:22:47 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	cur_idx;
	size_t	search_idx;

	cur_idx = 0;
	search_idx = ft_strlen(s) + 1;
	while (cur_idx < search_idx)
	{
		if (*((char *)s + cur_idx) == (char)c)
			return ((char *)s + cur_idx);
		cur_idx++;
	}
	return ((char *)(0));
}
