/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 08:58:43 by alee              #+#    #+#             */
/*   Updated: 2022/03/05 10:40:18 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	cur_idx;
	size_t	str_idx;

	if (!s1 || !s2)
		return ((char *)(0));
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str == (char *)0)
		return ((char *)(0));
	cur_idx = 0;
	str_idx = 0;
	while (*(s1 + cur_idx) != '\0')
	{
		*(str + str_idx++) = *(s1 + cur_idx++);
	}
	cur_idx = 0;
	while (*(s2 + cur_idx) != '\0')
	{
		*(str + str_idx) = *(s2 + cur_idx);
		cur_idx++;
		str_idx++;
	}
	*(str + str_idx) = '\0';
	return (str);
}
