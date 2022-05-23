/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:14:32 by alee              #+#    #+#             */
/*   Updated: 2022/05/23 18:25:03 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "../libft/libft.h"
#include "ft_env.h"

int	ft_env(char **cmd, t_shell_data *p_data)
{
	int	idx;

	if (!cmd || !(*cmd))
		return (1);
	idx = 0;
	print_env(cmd, &p_data->env_list);
	return (0);
}

void	print_env(char **cmd, t_env_list *p_list)
{
	t_env_node	*cur_node;
	//debug
	if (!cmd)
		return ;
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
