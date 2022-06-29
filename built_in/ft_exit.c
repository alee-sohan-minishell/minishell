/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 02:47:08 by alee              #+#    #+#             */
/*   Updated: 2022/06/29 20:49:11 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "ft_exit.h"
#include "../utils/command_utils_01.h"
#include "../utils/error_msg_utils_02.h"
#include "../built_in/ft_echo.h"
#include "../utils/integer_utils_01.h"

int	ft_exit(char **cmd, long long status)
{
	if (!cmd || !(*cmd))
		return (1);
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (get_cmd_count(cmd) == 1)
		exit(status);
	if (is_valid_num(cmd[1]) == 0)
		ft_self_perror_param_exit("exit", cmd[1], \
		"numeric argument required", 255);
	else if (get_cmd_count(cmd) > 2)
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	if (ft_atol(cmd[1], &status) == 0)
		ft_self_perror_param_exit("exit", cmd[1], \
		"numeric argument required", 255);
	exit((unsigned char)status);
	return (0);
}
