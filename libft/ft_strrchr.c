/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 00:51:47 by alee              #+#    #+#             */
/*   Updated: 2022/03/05 10:17:39 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	cur_idx;
	size_t	start_idx;
	char	*ptr;

	cur_idx = 0;
	start_idx = ft_strlen(s) + 1;
	ptr = (char *)0;
	while (cur_idx < start_idx)
	{
		if (*((char *)s + cur_idx) == (char)c)
			ptr = (char *)s + cur_idx;
		cur_idx++;
	}
	return (ptr);
}
