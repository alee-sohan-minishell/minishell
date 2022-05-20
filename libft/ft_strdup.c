/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 00:21:28 by alee              #+#    #+#             */
/*   Updated: 2022/03/05 10:22:30 by alee             ###   ########.fr       */
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
		return ((char *)(0));
	ft_memcpy(str, s1, cpy_len);
	return (str);
}
