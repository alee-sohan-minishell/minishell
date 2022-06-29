/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_execute_tree_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 08:16:44 by sohan             #+#    #+#             */
/*   Updated: 2022/06/29 08:16:46 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_execute.h"
#include <stdlib.h>
#include <unistd.h>

void	shell_execute_tree_init(t_shell_data *p_data)
{
	p_data->pipe_fd = malloc(p_data->pipe_count * sizeof(int [2]));
	p_data->pipe_status = malloc((p_data->pipe_count + 1) * sizeof(int));
	p_data->pipe_pid = malloc((p_data->pipe_count + 1) * sizeof(pid_t));
	p_data->fd_std[OUT] = dup(STDOUT_FILENO);
	p_data->fd_std[IN] = dup(STDIN_FILENO);
	p_data->is_piped = 0;
	p_data->cmd_count = 0;
	p_data->fileio_errno = 0;
	p_data->fd_new[OUT] = 0;
	p_data->fd_new[IN] = 0;
	p_data->pipe_num = p_data->pipe_count;
}

void	close_pipe_fd(t_shell_data *p_data)
{
	int	index;

	index = 0;
	while (index < p_data->pipe_count)
	{
		close(p_data->pipe_fd[index][READ]);
		close(p_data->pipe_fd[index][WRITE]);
		++index;
	}
}

void	restore_stdio(int fd_std[])
{
	dup2(fd_std[OUT], STDOUT_FILENO);
	dup2(fd_std[IN], STDIN_FILENO);
	close(fd_std[OUT]);
	close(fd_std[IN]);
}
