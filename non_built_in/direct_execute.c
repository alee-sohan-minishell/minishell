/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 08:50:16 by sohan             #+#    #+#             */
/*   Updated: 2022/06/29 18:26:48 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "non_built_in.h"
#include "../utils/error_msg_utils_01.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

static void	force_execute_no_shebang(t_shell_data *p_data)
{
	char	*cmd[3];

	cmd[0] = "/bin/sh";
	cmd[1] = p_data->cmd[0];
	cmd[2] = NULL;
	execve("/bin/sh", cmd, NULL);
}

static void	execute_without_path(t_shell_data *p_data)
{
	struct stat	s;

	if (execve(p_data->cmd[0], p_data->cmd, *p_data->p_env) == -1)
	{
		if (errno == ENOEXEC)
			force_execute_no_shebang(p_data);
		if (errno != ENOENT && errno != EACCES)
		{
			ft_self_perror_param(NULL, p_data->cmd[0], strerror(errno));
			exit(126);
		}
		else if (errno == EACCES)
		{
			if (stat(p_data->cmd[0], &s) == -1 || s.st_mode & S_IFREG)
				ft_self_perror_param(NULL, p_data->cmd[0], strerror(errno));
			else
				ft_self_perror_param(NULL, p_data->cmd[0], "is a directory");
			exit(126);
		}
		else
		{
			ft_self_perror_param(NULL, p_data->cmd[0], strerror(errno));
			exit(127);
		}
	}
}

void	direct_execute(t_shell_data *p_data)
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
				execute_without_path(p_data);
			else
				exit(p_data->fileio_errno);
		}
	}
	else
	{
		if (p_data->fileio_errno == 0)
			execute_without_path(p_data);
		else
			exit(p_data->fileio_errno);
	}
}
