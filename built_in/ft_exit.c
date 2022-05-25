/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 02:47:08 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 13:50:33 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "ft_exit.h"
#include "../utils/command_utils_01.h"
#include "../utils/error_msg_utils_01.h"
#include "../built_in/ft_echo.h"
#include "../utils/integer_utils_01.h"

int	ft_exit(char **cmd, long long status)
{
	if (!cmd || !(*cmd))
		return (1);
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (get_cmd_count(cmd) == 1)
		exit(0);
	if (is_valid_num(cmd[1]) == 0)
		ft_msg_exit("exit: numeric argument required", 255, STDERR_FILENO);
	else if (get_cmd_count(cmd) > 2)
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	if (ft_atol(cmd[1], &status) == 0)
		ft_msg_exit("exit: numeric argument required", 255, STDERR_FILENO);
	exit((unsigned char)status);
	return (0);
}
