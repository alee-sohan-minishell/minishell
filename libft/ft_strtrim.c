/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 06:11:34 by alee              #+#    #+#             */
/*   Updated: 2022/03/05 10:39:17 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(int c, const char *set)
{
	if (ft_strchr(set, c))
		return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s_idx;
	size_t	e_idx;
	char	*str;

	if (!s1)
		return ((char *)(0));
	if (!set)
		return (ft_strdup(s1));
	s_idx = 0;
	e_idx = ft_strlen(s1);
	while (ft_isset(*(s1 + s_idx), set) && *(s1 + s_idx) != '\0')
		s_idx++;
	while (ft_isset(*(s1 + e_idx), set) && (s1 + e_idx) != s1)
		e_idx--;
	if (s_idx > e_idx)
		return (ft_strdup(""));
	str = (char *)malloc(e_idx - s_idx + 1 + 1);
	if (str == (char *)0)
		return ((char *)(0));
	ft_strlcpy(str, s1 + s_idx, e_idx - s_idx + 2);
	return (str);
}
