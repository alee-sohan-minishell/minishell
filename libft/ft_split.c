/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 11:27:08 by alee              #+#    #+#             */
/*   Updated: 2022/03/05 10:42:31 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_split_count(char const *s, char c)
{
	size_t	split_count;
	size_t	cur_idx;

	split_count = 0;
	cur_idx = 0;
	while (*(s + cur_idx) != '\0')
	{
		if (*(s + cur_idx) == c)
		{
			while (*(s + cur_idx) == c)
				cur_idx++;
		}
		else if (*(s + cur_idx) != c)
		{
			if (*(s + cur_idx) == '\0')
				break ;
			split_count++;
			while (*(s + cur_idx) != c && *(s + cur_idx) != '\0')
				cur_idx++;
		}
	}
	return (split_count);
}

static char	**ft_free_str(char **str)
{
	size_t	cur_idx;

	cur_idx = 0;
	while (*(str + cur_idx))
		free(*(str + cur_idx));
	free(str);
	return ((char **)(0));
}

static size_t	ft_str_info(char const *s, char c, size_t *str_len)
{
	size_t	cur_idx;
	size_t	start_idx;
	size_t	end_idx;

	cur_idx = 0;
	start_idx = 0;
	end_idx = 0;
	while (*(s + cur_idx) == c)
		cur_idx++;
	start_idx = cur_idx;
	while (*(s + cur_idx) != c && *(s + cur_idx) != '\0')
		cur_idx++;
	end_idx = cur_idx;
	*str_len = end_idx - start_idx;
	return (cur_idx);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	cur_idx;
	size_t	split_cnt;
	size_t	str_idx;
	size_t	str_len;

	if (!s)
		return ((char **)(0));
	split_cnt = ft_split_count(s, c);
	str = (char **)malloc(sizeof(char *) * (split_cnt + 1));
	if (!str)
		return ((char **)(0));
	cur_idx = 0;
	str_idx = 0;
	while (cur_idx < split_cnt)
	{
		str_idx += ft_str_info(s + str_idx, c, &str_len);
		str[cur_idx] = (char *)malloc(str_len + 1);
		if (!str[cur_idx])
			return (ft_free_str(str));
		ft_strlcpy(str[cur_idx++], s + str_idx - str_len, str_len + 1);
	}
	str[cur_idx] = (char *)(0);
	return (str);
}
