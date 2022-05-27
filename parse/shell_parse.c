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

/****************temp implementation**********/
#include "../env/env_list_interface_01.h"

void	get_cmd_blocks(t_shell_data *p_data)
{
	char		**cmd;
	int			index;

	index = 0;
	cmd = ft_split(p_data->line, ';');
	if (!cmd)
	{
		ft_set_status(p_data, S_ERROR);
		return ;
	}
	while (cmd[index])
		++index;
	p_data->cmd_block = ft_calloc(index + 1, sizeof(char **));
	if (!p_data->cmd_block)
	{
		ft_set_status(p_data, S_ERROR);
		return ;
	}
	index = 0;
	while (cmd[index])
	{
		p_data->cmd_block[index] = ft_split(cmd[index], ' ');
		if (!p_data->cmd_block[index])
		{
			ft_set_status(p_data, S_ERROR);
			return ;
		}
		free(cmd[index]);
		++index;
	}
	p_data->cmd_block[index] = NULL;
	free(cmd);
	p_data->cmd = p_data->cmd_block[0];
}
/****************** to here********************/

void	shell_parse(t_shell_data *p_data)
{
	if (!p_data)
		return ;
	get_cmd_blocks(p_data);
	/*p_data->cmd = ft_split(p_data->line, ' ');
	if (!p_data->cmd)
	{
		ft_set_status(p_data, S_ERROR);
		return ;
	}*/
	ft_set_status(p_data, S_CMD);
	return ;
}
