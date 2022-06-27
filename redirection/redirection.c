/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 02:03:49 by alee              #+#    #+#             */
/*   Updated: 2022/05/28 07:10:13 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/command_utils_01.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include "../utils/fd_utils_01.h"
#include "../utils/error_msg_utils_01.h"
#include "../shell/shell.h"
#include <errno.h>

int	redirection_in(t_shell_data *p_data, const char *file)
{
	int	file_fd;

	file_fd = open(file, O_RDONLY);
	if (file_fd == -1)
	{
		ft_perror_param((const char *)0, file, errno);
		p_data->global_data.pipe_status[p_data->cmd_count] = 1;
		p_data->fileio_errno = 1;
		return (-1);
	}
	p_data->global_data.pipe_status[p_data->cmd_count] = 0;
	p_data->fileio_errno = 0;
	p_data->fd_in_new = file_fd;
	ft_dup2(file_fd, STDIN_FILENO);
	ft_close(file_fd);
	return (0);
}

int	redirection_out(t_shell_data *p_data, const char *file)
{
	int	file_fd;

	file_fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (file_fd == -1)
	{
		ft_perror_param((const char *)0, file, 1);
		p_data->fileio_errno = 1;
		p_data->global_data.pipe_status[p_data->cmd_count] = 1;
		return (-1);
	}
	p_data->global_data.pipe_status[p_data->cmd_count] = 0;
	p_data->fileio_errno = 0;
	p_data->fd_out_new = file_fd;
	ft_dup2(file_fd, STDOUT_FILENO);
	ft_close(file_fd);
	return (0);
}

int	redirection_append(t_shell_data *p_data, const char *file)
{
	int	file_fd;

	file_fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (file_fd == -1)
	{
		ft_perror_param((const char *)0, file, 1);
		p_data->fileio_errno = 1;
		p_data->global_data.pipe_status[p_data->cmd_count] = 1;
		return (-1);
	}
	p_data->global_data.pipe_status[p_data->cmd_count] = 0;
	p_data->fileio_errno = 0;
	p_data->fd_out_new = file_fd;
	ft_dup2(file_fd, STDOUT_FILENO);
	ft_close(file_fd);
	return (0);
}
