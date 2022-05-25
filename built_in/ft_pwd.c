/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:25:22 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 05:51:03 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../libft/libft.h"
#include "../utils/error_msg_utils_01.h"

int	ft_pwd(char **cmd)
{
	char	*path;

	if (!cmd)
		return (0);
	path = getcwd((char *)0, 0);
	if (!path)
		ft_perror_exit(cmd[0], 1);
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	return (0);
}
