/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:14:32 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 15:54:57 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "../libft/libft.h"
#include "../built_in/ft_exit.h"
#include "ft_env.h"
#include "../utils/command_utils_01.h"
#include "../utils/error_msg_utils_01.h"
#include "../env/env_list_interface_01.h"

int	ft_env(char **cmd, t_shell_data *p_data)
{
	t_env_node	*o_env_path;

	if (!cmd || !(*cmd))
		return (1);
	if (get_cmd_count(cmd) > 1)
	{
		if (ft_strcmp(cmd[1], "~") == 0)
		{
			if (env_node_search(&p_data->env_list, "HOME", &o_env_path) == 0)
				ft_self_perror_param("env", p_data->env_default_home, \
				"Permission denied");
			else
				ft_self_perror_param("env", o_env_path->value, \
				"Permission denied");
			return (126);
		}
		else
		{
			ft_self_perror_param("env", cmd[1], "No such file or directory");
			return (127);
		}
	}
	print_env(&p_data->env_list);
	return (0);
}

void	print_env(t_env_list *p_list)
{
	t_env_node	*cur_node;

	cur_node = p_list->dummy_head.next;
	while (cur_node != &p_list->dummy_tail)
	{
		if (cur_node->value)
		{
			ft_putstr_fd(cur_node->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(cur_node->value, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		cur_node = cur_node->next;
	}
	return ;
}
