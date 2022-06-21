/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils_01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 03:01:59 by alee              #+#    #+#             */
/*   Updated: 2022/06/21 13:51:12 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "fd_utils_01.h"
#include "error_msg_utils_01.h"
#include "../shell/shell.h"

int	ft_dup(int fd)
{
	int	new_fd;

	new_fd = dup(fd);
	if (new_fd == -1)
	{
		ft_perror(STR_SHELL);
		exit(1);
	}
	return (new_fd);
}

int	ft_dup2(int fildes, int fildes2)
{
	int	result;

	result = dup2(fildes, fildes2);
	if (result == -1)
	{
		ft_perror(STR_SHELL);
		exit(1);
	}
	return (result);
}


int	ft_close(int fd)
{
	int	close_fd;

	close_fd = close(fd);
	if (close_fd == -1)
		ft_perror((const char *)0);
	return (close_fd);
}

void	recover_default_fd(t_shell_data *p_data)
{
	ft_dup2(p_data->cp_stdin, STDIN_FILENO);
	ft_dup2(p_data->cp_stdout, STDOUT_FILENO);
	ft_dup2(p_data->cp_stderr, STDERR_FILENO);
	return ;
}
