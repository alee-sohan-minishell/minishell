/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 08:16:10 by sohan             #+#    #+#             */
/*   Updated: 2022/06/29 18:25:48 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_execute.h"
#include <unistd.h>

void	close_pipe_fd_from_start(t_shell_data *p_data)
{
	int	index;

	index = 0;
	while (index < p_data->cmd_count - 1)
	{
		close(p_data->pipe_fd[index][READ]);
		close(p_data->pipe_fd[index][WRITE]);
		++index;
	}
}

void	close_pipe_fd_to_end(t_shell_data *p_data)
{
	int	index;

	index = p_data->cmd_count + 1;
	while (index < p_data->pipe_count)
	{
		close(p_data->pipe_fd[index][READ]);
		close(p_data->pipe_fd[index][WRITE]);
		++index;
	}
}

void	set_io_child(t_shell_data *p_data)
{
	if (p_data->cmd_count < p_data->pipe_count)
	{
		close_pipe_fd_from_start(p_data);
		close(p_data->pipe_fd[p_data->cmd_count][READ]);
		if (!p_data->fd_new[OUT])
			dup2(p_data->pipe_fd[p_data->cmd_count][WRITE], STDOUT_FILENO);
		close(p_data->pipe_fd[p_data->cmd_count][WRITE]);
		close_pipe_fd_to_end(p_data);
	}
	else
	{
		if (!p_data->fd_new[OUT])
		{
			dup2(p_data->fd_std[OUT], STDOUT_FILENO);
			close(p_data->fd_std[OUT]);
		}
	}
}

void	set_io_parent(t_shell_data *p_data)
{
	if (p_data->cmd_count < p_data->pipe_count)
	{
		close(p_data->pipe_fd[p_data->cmd_count][WRITE]);
		dup2(p_data->pipe_fd[p_data->cmd_count][READ], STDIN_FILENO);
		close(p_data->pipe_fd[p_data->cmd_count][READ]);
	}
}
