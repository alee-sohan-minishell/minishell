/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils_01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 03:01:59 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 03:35:06 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "fd_utils_01.h"
#include "error_msg_utils_01.h"

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
