/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:57:11 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 08:45:26 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../libft/libft.h"
#include "ft_cd.h"
#include "../utils/error_msg_utils_01.h"
#include "../utils/command_utils_01.h"
#include "../shell/shell.h"
#include "../env/env_list_interface_01.h"

int	ft_cd(char **cmd, t_shell_data *p_data)
{
	int		ret;
	char	*o_home_path;

	if (!cmd || !(*cmd))
		return (1);
	ret = 0;
	o_home_path = (char *)0;
	if (cmd[0])
	{
		if (is_chdir_home(cmd, &o_home_path, p_data) == 1)
		{
			if (o_home_path)
				ret = chdir(o_home_path);
		}
		else
			ret = chdir(cmd[1]);
		if (ret == -1)
		{
			ft_perror_param("cd", cmd[1], 1);
			return (1);
		}
	}
	return (0);
}

int	is_chdir_home(char **cmd, char **o_home_path, t_shell_data *p_data)
{
	t_env_node	*home_node;

	if (get_cmd_count(cmd) == 1)
	{
		if (env_node_search(&p_data->env_list, "HOME", &home_node) == 0)
			ft_perror_param("cd", "HOME not set", 0);
		else
			*o_home_path = home_node->value;
	}
	if (get_cmd_count(cmd) > 1 && ft_strcmp(cmd[1], "~") == 0)
		*o_home_path = p_data->env_default_home;
	else
		return (0);
	return (1);
}
