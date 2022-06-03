/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:08:02 by alee              #+#    #+#             */
/*   Updated: 2022/05/30 01:36:16 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "../utils/state_machine_utils_01.h"
#include "../libft/libft.h"

void	shell_parse(t_shell_data *p_data)
{
	if (!p_data)
		return ;
	p_data->cmd = ft_split(p_data->line, ' '); //# cmd 지우고 p_data->line에서 parse 해서 tree 만들기
	if (!p_data->cmd)
	{
		ft_set_status(p_data, S_ERROR);
		return ;
	}
	ft_set_status(p_data, S_CMD);
	return ;
}

//# 여러 개 찾는 걸로 바꾸기
/*char	*ft_strchr(const char *s, int c)
{
	size_t	cur_idx;
	size_t	search_idx;

	cur_idx = 0;
	search_idx = ft_strlen(s) + 1;
	while (cur_idx < search_idx)
	{
		if (*((char *)s + cur_idx) == (char)c)
			return ((char *)s + cur_idx);
		cur_idx++;
	}
}*/
