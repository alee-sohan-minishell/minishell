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

int	redirection_in(const char *file)
{
	int	file_fd;

	file_fd = open(file, O_RDONLY);
	if (file_fd == -1)
	{
		ft_perror_param((const char *)0, file, 1);
		return (-1);
	}
	ft_dup2(file_fd, STDOUT_FILENO);
	ft_close(file_fd);
	return (1);
}

int	redirection_out(const char *file)
{
	int	file_fd;

	file_fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (file_fd == -1)
	{
		ft_perror_param((const char *)0, file, 1);
		return (-1);
	}
	ft_dup2(file_fd, STDOUT_FILENO);
	ft_close(file_fd);
	return (1);
}

int	redirection_append(const char *file)
{
	int	file_fd;

	file_fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (file_fd == -1)
	{
		ft_perror_param((const char *)0, file, 1);
		return (-1);
	}
	ft_dup2(file_fd, STDOUT_FILENO);
	ft_close(file_fd);
	return (1);
}
