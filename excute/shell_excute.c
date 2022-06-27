/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_excute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:09:58 by alee              #+#    #+#             */
/*   Updated: 2022/06/28 01:52:47 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "../libft/libft.h"
#include "../utils/state_machine_utils_01.h"
#include "../built_in/ft_cd.h"
#include "../built_in/ft_pwd.h"
#include "../built_in/ft_echo.h"
#include "../built_in/ft_exit.h"
#include "../built_in/ft_env.h"
#include "../built_in/ft_unset.h"
#include "../built_in/ft_export.h"
#include "../non_built_in/non_built_in.h"
#include "../init/shell_utils_01.h"

void	shell_execute(t_shell_data *p_data)
{
	if (!p_data)
		return ;
	if (!p_data->cmd[0])
		ft_set_status(p_data, S_LINE_READ);
	else if (ft_strcmp(p_data->cmd[0], "cd") == 0)
		p_data->global_data.pipe_status[p_data->cmd_count] = ft_cd(p_data->cmd, p_data);
	else if (ft_strcmp(p_data->cmd[0], "pwd") == 0)
		p_data->global_data.pipe_status[p_data->cmd_count] = ft_pwd(p_data->cmd);
	else if (ft_strcmp(p_data->cmd[0], "echo") == 0)
		p_data->global_data.pipe_status[p_data->cmd_count] = ft_echo(p_data->cmd, p_data);
	else if (ft_strcmp(p_data->cmd[0], "exit") == 0)
		p_data->global_data.pipe_status[p_data->cmd_count] = ft_exit(p_data->cmd, p_data->last_status);
	else if (ft_strcmp(p_data->cmd[0], "env") == 0)
		p_data->global_data.pipe_status[p_data->cmd_count] = ft_env(p_data->cmd, p_data);
	else if (ft_strcmp(p_data->cmd[0], "unset") == 0)
		p_data->global_data.pipe_status[p_data->cmd_count] = ft_unset(p_data->cmd, &p_data->env_list);
	else if (ft_strcmp(p_data->cmd[0], "export") == 0)
		p_data->global_data.pipe_status[p_data->cmd_count] = ft_export(p_data->cmd, &p_data->env_list);
	else
	{
		ft_exec_command(p_data);
		set_tc_attr(p_data);
	}
	ft_set_status(p_data, S_LINE_READ);
	return ;
}
