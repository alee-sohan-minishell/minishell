/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_excute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:09:58 by alee              #+#    #+#             */
/*   Updated: 2022/05/28 04:03:43 by alee             ###   ########.fr       */
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

//debug
#include "../redirection/redirection.h"

void	shell_excute(t_shell_data *p_data)
{
	if (!p_data)
		return ;
	//if (!p_data->cmd)
	if (!p_data->cmd[0])
		ft_set_status(p_data, S_LINE_READ);
	else if (ft_strcmp(p_data->cmd[0], "cd") == 0)
		ft_cd(p_data->cmd, p_data);
	else if (ft_strcmp(p_data->cmd[0], "pwd") == 0)
		ft_pwd(p_data->cmd);
	else if (ft_strcmp(p_data->cmd[0], "redi") == 0)
	{
		execv("/bin/echo", NULL);
		printf("redirection test \n");
	}
	else if (ft_strcmp(p_data->cmd[0], "echo") == 0)
		ft_echo(p_data->cmd, p_data);
	else if (ft_strcmp(p_data->cmd[0], "exit") == 0)
		ft_exit(p_data->cmd, 1);
	else if (ft_strcmp(p_data->cmd[0], "env") == 0)
		ft_env(p_data->cmd, p_data);
	else if (ft_strcmp(p_data->cmd[0], "unset") == 0)
		ft_unset(p_data->cmd, &p_data->env_list);
	else if (ft_strcmp(p_data->cmd[0], "export") == 0)
		ft_export(p_data->cmd, &p_data->env_list);
	else if (ft_strcmp(p_data->cmd[0], "break") == 0)
	{
		ft_set_status(p_data, S_ERROR);
		return ;
	}
	else
	{
		dup2(p_data->fd_out_old, STDOUT_FILENO);
		close(p_data->fd_out_old);
		ft_exec_command(p_data);
		set_tc_attr(p_data);
		dup2(p_data->fd_in_old, STDIN_FILENO);
		close(p_data->fd_in_old);
		//printf("%d\n", p_data->term_status);
	}


	/*	split free	*/
	/*int	idx;

	idx = 0;
	while (p_data->cmd && p_data->cmd[idx])
	{
		free(p_data->cmd[idx]);
		idx++;
	}
	//free(p_data->cmd[idx]);
	if (p_data->cmd)
		free(p_data->cmd);*/
	/*	-------------------------	*/

	/*	line string free	*/
	//if (p_data->line)
	//	free(p_data->line);
	/*	-------------------------	*/
	/*	default home path free -> 프로그램 종료	*/
	/*	env list free -> 프로그램 종료	*/
	//set_tc_attr(p_data);
	ft_set_status(p_data, S_LINE_READ);
	return ;
}
