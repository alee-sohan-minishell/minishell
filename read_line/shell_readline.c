/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 05:40:09 by alee              #+#    #+#             */
/*   Updated: 2022/05/23 18:12:59 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "shell_readline.h"
#include "../utils/utils_02.h"

//debug
#include <string.h>
#include "../built_in/ft_pwd.h"
#include "../built_in/ft_cd.h"
#include "../built_in/ft_echo.h"
#include "../built_in/ft_exit.h"
#include "../built_in/ft_env.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include "../signal/signal.h"
#include "../init/shell_init.h"
#include "../non_built_in/non_built_in.h"

void	shell_readline(t_shell_data *p_data)
{
	set_signal_background();
	p_data->line = readline(p_data->prompt_msg);
	if (!p_data->line)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		p_data->status = S_ERROR;
		set_tc_attr_to_default(p_data);
		return ;
	}
	/*	ADD HISTORY	*/
	insert_cmd_history(p_data->line);
	/*	Set Status	*/
	// ft_set_status(p_data, S_CMD);
	/*	Temp Parsing	*/
	p_data->cmd = ft_split(p_data->line, ' ');
	if (!p_data->cmd)
	{
		p_data->status = S_ERROR;
		return ;
	}
	if (!p_data->cmd[0])
		p_data->status = S_LINE_READ;
	else if (strcmp(p_data->cmd[0], "cd") == 0)
		ft_cd(p_data->cmd);
	else if (strcmp(p_data->cmd[0], "pwd") == 0)
		ft_pwd(p_data->cmd);
	else if (strcmp(p_data->cmd[0], "echo") == 0)
		ft_echo(p_data->cmd);
	else if (strcmp(p_data->cmd[0], "exit") == 0)
		ft_exit(p_data->cmd, 1);
	else if (strcmp(p_data->cmd[0], "env") == 0)
		ft_env(p_data->cmd, p_data);
	else
		ft_exec_command(p_data);
	if (p_data->line)//free line string
		free(p_data->line);
	set_tc_attr(p_data);
	return ;
}

void	insert_cmd_history(const char *cmd)
{
	add_history(cmd);
	return ;
}

//파싱, 트리구조(추상구문트리),

//alee : 빌트인, env, export, unset

//min-jo : tree, redirection, pipe

//sohan : Unit test, parsing
