/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:14:32 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 10:15:14 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "../libft/libft.h"
#include "../built_in/ft_exit.h"
#include "ft_env.h"
#include "../utils/command_utils_01.h"
#include "../utils/error_msg_utils_01.h"

int	ft_env(char **cmd, t_shell_data *p_data)
{
	if (!cmd || !(*cmd))
		return (1);
	if (get_cmd_count(cmd) > 1)
	{
		ft_custom_perror_param("env", cmd[1], "No such file or directory");
		return (127);
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
		ft_putstr_fd(cur_node->key, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putendl_fd(cur_node->value, STDOUT_FILENO);
		cur_node = cur_node->next;
	}
	return ;
}
