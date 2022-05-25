/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_utils_01.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 04:38:03 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 04:32:01 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include <stdlib.h>

void	ft_set_status(t_shell_data *p_data, t_shell_status status)
{
	p_data->status = status;
	return ;
}

int		status_close(t_shell_data *p_data)
{
	//Default HOME PATH
	if (p_data->env_default_home)
		free(p_data->env_default_home);
	//ENV LIST
	if (p_data->env_list.node_count == 0)
		return (0);
	/*	TODO : 메모리 할당 모두 해제	*/
	return (1);
}
