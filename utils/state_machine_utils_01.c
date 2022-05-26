/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_utils_01.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 04:38:03 by alee              #+#    #+#             */
/*   Updated: 2022/05/26 14:26:11 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include <stdlib.h>
#include "../env/env_list_interface_01.h"

void	ft_set_status(t_shell_data *p_data, t_shell_status status)
{
	p_data->status = status;
	return ;
}

int	status_close(t_shell_data *p_data)
{
	if (!p_data)
		return (0);
	if (p_data->env_default_home)
		free(p_data->env_default_home);
	env_node_clear(&p_data->env_list);
	return (1);
}
