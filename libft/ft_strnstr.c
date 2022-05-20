/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 06:49:28 by alee              #+#    #+#             */
/*   Updated: 2022/03/05 10:18:03 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	cur_idx;
	size_t	needle_len;
	size_t	haystack_len;

	cur_idx = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	haystack_len = ft_strlen(haystack);
	needle_len = ft_strlen(needle);
	if (needle_len > len || needle_len > haystack_len)
		return ((char *)(0));
	while (cur_idx < len - needle_len + 1)
	{
		if (*((char *)haystack + cur_idx) == *needle)
		{
			if (ft_strncmp(haystack + cur_idx, needle, needle_len) == 0)
				return ((char *)haystack + cur_idx);
		}
		cur_idx++;
	}
	return ((char *)(0));
}
