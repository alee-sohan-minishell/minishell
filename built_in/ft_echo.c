/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:06:41 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 15:24:38 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../libft/libft.h"
#include "ft_echo.h"
#include "../shell/shell.h"
#include "../env/env_list_interface_01.h"

int	ft_echo(char **cmd, t_shell_data *p_data)
{
	int	newline_flag;
	int	space_idx;
	int	idx;

	if (!cmd || !(*cmd))
		return (1);
	newline_flag = is_newline_flag(&cmd[1]);
	space_idx = 0;
	idx = 1 + newline_flag;
	while (cmd[idx])
	{
		if (space_idx)
			ft_putstr_fd(" ", STDOUT_FILENO);
		print_echo(cmd[idx], p_data);
		idx++;
		space_idx++;
	}
	if (newline_flag == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

int	is_newline_flag(char **cmd)
{
	int	n_flag;
	int	idx;

	idx = 0;
	n_flag = 0;
	while (cmd[idx])
	{
		if (ft_strcmp(cmd[idx], "-n") == 0)
			n_flag += 1;
		else if (ft_strlen(cmd[idx]) > ft_strlen("-n"))
			n_flag += is_continuous_opt_value(cmd[idx], '-', 'n');
		else
			break ;
		idx++;
	}
	return (n_flag);
}

int	is_continuous_opt_value(const char *line, char opt_flag, char opt_value)
{
	int	idx;
	int	ret;

	idx = 0;
	ret = 0;
	while (line[idx])
	{
		if (idx == 0)
		{
			if (line[idx] != opt_flag)
				return (ret);
		}
		else
		{
			if (line[idx] != opt_value)
				return (ret);
		}
		idx++;
	}
	ret = 1;
	return (ret);
}

int	is_hashtag_flag(const char *line)
{
	if (ft_strncmp(line, "#", 1) == 0)
		return (1);
	if (is_continuous_opt_value(line, '#', '#'))
		return (1);
	return (0);
}

void	print_echo(char *line, t_shell_data *p_data)
{
	t_env_node	*cur_node;

	if (ft_strcmp(line, "~") == 0)
	{
		if (env_node_search(&p_data->env_list, "HOME", &cur_node) == 0)
			ft_putstr_fd(p_data->env_default_home, STDOUT_FILENO);
		else
			ft_putstr_fd(cur_node->value, STDOUT_FILENO);
	}
	else
		ft_putstr_fd(line, STDOUT_FILENO);
	return ;
}
