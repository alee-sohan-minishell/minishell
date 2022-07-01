/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan<sohan@student.42seoul.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 08:50:38 by sohan             #+#    #+#             */
/*   Updated: 2022/06/29 18:26:56 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "non_built_in.h"
#include "../utils/error_msg_utils_01.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

void	execute_with_path(t_shell_data *p_data, char *path)
{
	pid_t	pid;

	if (!p_data->is_piped)
	{
		pid = fork();
		if (pid > 0)
			p_data->pipe_pid[p_data->cmd_count] = pid;
		else if (pid == 0)
		{
			if (p_data->fileio_errno == 0)
				execve(path, p_data->cmd, *p_data->p_env);
			else
				exit(p_data->fileio_errno);
		}
	}
	else
	{
		if (p_data->fileio_errno == 0)
			execve(path, p_data->cmd, *p_data->p_env);
		else
			exit(p_data->fileio_errno);
	}
}

void	set_commnad_not_found(t_shell_data *p_data)
{
	ft_self_perror_param(NULL, p_data->cmd[0], "command not found");
	p_data->pipe_status[p_data->cmd_count] = 127;
	if (p_data->is_piped)
		exit(127);
}

void	search_execute(t_shell_data *p_data, char **path_list)
{
	int			index;
	struct stat	s;

	index = 0;
	while (path_list[index])
	{
		if (stat(path_list[index], &s) == 0)
		{
			execute_with_path(p_data, path_list[index]);
			break ;
		}
		++index;
	}
	if (!path_list[index])
		set_commnad_not_found(p_data);
}
