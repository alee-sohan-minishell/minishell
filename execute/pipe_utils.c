/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan<sohan@student.42seoul.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 08:16:10 by sohan             #+#    #+#             */
/*   Updated: 2022/06/29 18:25:48 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_execute.h"
#include <unistd.h>

void	set_io_child(t_shell_data *p_data, int pipe_fd[])
{
	if (p_data->cmd_count < p_data->pipe_count)
	{
		close(pipe_fd[READ]);
		if (!p_data->fd_new[OUT])
			dup2(pipe_fd[WRITE], STDOUT_FILENO);
		close(pipe_fd[WRITE]);
	}
	else
	{
		if (!p_data->fd_new[OUT])
			dup2(p_data->cp_stdout, STDOUT_FILENO);
	}
}

void	set_io_parent(t_shell_data *p_data, int pipe_fd[])
{
	if (p_data->cmd_count < p_data->pipe_count)
	{
		close(pipe_fd[WRITE]);
		dup2(pipe_fd[READ], STDIN_FILENO);
		close(pipe_fd[READ]);
	}
}
