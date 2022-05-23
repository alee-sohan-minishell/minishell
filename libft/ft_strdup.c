/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 00:21:28 by alee              #+#    #+#             */
/*   Updated: 2022/05/23 03:17:45 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	cpy_len;

	cpy_len = ft_strlen(s1) + 1;
	str = (char *)malloc(sizeof(char) * cpy_len);
	if (!str)
		return ((char *)0);
	ft_memcpy(str, s1, cpy_len);
	return (str);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*str;
	size_t	s_len;

	s_len = ft_strlen(s1);
	if (s_len < n)
		n = s_len;
	str = (char *)malloc(n + 1);
	if (!str)
		return ((char *)0);
	ft_memcpy(str, s1, n);
	str[n] = '\0';
	return (str);
}
