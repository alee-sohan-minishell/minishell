/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 08:29:05 by alee              #+#    #+#             */
/*   Updated: 2022/03/05 10:19:18 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	s_len;
	size_t	cur_idx;
	char	*str;

	if (!s)
		return ((char *)(0));
	s_len = ft_strlen(s);
	str = (char *)malloc(s_len + 1);
	if (!str)
		return ((char *)(0));
	cur_idx = 0;
	while (cur_idx < s_len)
	{
		*(str + cur_idx) = f(cur_idx, *(s + cur_idx));
		cur_idx++;
	}
	*(str + cur_idx) = '\0';
	return (str);
}
