/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 09:08:26 by alee              #+#    #+#             */
/*   Updated: 2022/03/05 10:16:06 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	str_len;
	size_t	alloc_len;

	if (!s)
		return ((char *)(0));
	alloc_len = 0;
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (ft_strdup(""));
	if (start + len > str_len)
		alloc_len = str_len - start;
	else
		alloc_len = len;
	str = (char *)malloc(alloc_len + 1);
	if (!str)
		return ((char *)(0));
	ft_strlcpy(str, s + start, alloc_len + 1);
	return (str);
}
