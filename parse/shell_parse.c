/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:08:02 by alee              #+#    #+#             */
/*   Updated: 2022/05/26 13:16:45 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "../utils/state_machine_utils_01.h"
#include "../libft/libft.h"

void	shell_parse(t_shell_data *p_data)
{
	if (!p_data)
		return ;
	p_data->cmd = ft_split(p_data->line, ' ');
	if (!p_data->cmd)
	{
		ft_set_status(p_data, S_ERROR);
		return ;
	}
	ft_set_status(p_data, S_CMD);
	return ;
}
