/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 07:50:44 by alee              #+#    #+#             */
/*   Updated: 2022/05/16 05:37:05 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "../libft/libft.h"
#include "utils_01.h"

int	ft_dup(int fd)
{
	int	new_fd;

	new_fd = dup(fd);
	if (new_fd == -1)
		ft_perror((const char *)0);
	return (new_fd);
}

int	ft_close(int fd)
{
	int	close_fd;

	close_fd = close(fd);
	if (close_fd == -1)
		ft_perror((const char *)0);
	return (close_fd);
}

void	ft_perror(const char *msg)
{
	char	buf[512];
	char	*e_msg;

	buf[0] = '\0';
	e_msg = strerror(errno);
	if (msg)
	{
		ft_strlcat(buf, msg, sizeof(buf));
		ft_strlcat(buf, ": ", sizeof(buf));
	}
	if (e_msg)
		ft_strlcat(buf, e_msg, sizeof(buf));
	ft_putendl_fd(buf, STDERR_FILENO);
	return ;
}

void	ft_perror_exit(const char *msg, int exit_status)
{
	ft_perror(msg);
	exit(exit_status);
}
