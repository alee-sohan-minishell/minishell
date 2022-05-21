/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 02:47:08 by alee              #+#    #+#             */
/*   Updated: 2022/05/21 15:02:47 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "ft_exit.h"
#include "../utils/utils_01.h"
#include "../built_in/ft_echo.h"
#include "../libft/libft.h"

int	ft_exit(char **cmd, long long status)
{
	if (!cmd || !(*cmd))
		return (1);
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (get_cmd_count(cmd) == 1 || is_hashtag_flag(cmd[1]))
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

int	get_cmd_count(char **cmd)
{
	int	idx;

	if (!cmd)
		return (0);
	idx = 0;
	while (cmd[idx])
		idx++;
	return (idx);
}

int	is_valid_num(char *str)
{
	int	idx;

	if (!str)
		return (0);
	idx = 0;
	if (str[idx] == '+' || str[idx] == '-')
		idx++;
	while (str[idx])
	{
		if (ft_isdigit(str[idx]) == 0)
			return (0);
		idx++;
	}
	return (1);
}


int	ft_atol(char *str, long long *o_var)
{
	long long	ret;
	int			idx;
	int			sign;
	int			flow_flag;

	ret = 0;
	idx = 0;
	sign = 1;
	flow_flag = 0;
	if (str[idx] == '-' || str[idx] == '+')
	{
		if (str[idx] == '-')
			sign = -1;
		idx++;
	}
	while (ft_isdigit(str[idx]))
	{
		ret *= 10;
		ret += str[idx++] - '0';
	}
	*o_var = ret * sign;
	if ((sign == 1 && ret < 0) || (sign == -1 && ret * sign > 0))
		return (0);
	return (1);
}
