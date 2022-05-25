/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 03:50:29 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 12:12:56 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

int	is_variable_rule(char ch)
{
	if (ch == '_')
		return (1);
	if (ft_isalpha(ch))
		return (1);
	return (0);
}


char	*parse_key(const char *line)
{
	int	sep;

	if (!line)
		return ((char *)0);
	if (ft_strchr(line, '=') == 0)
		return (ft_strdup(line));
	sep = 0;
	// sep = ft_strlen(line) - ;

	// ft_strndup(
	return (NULL);
}
