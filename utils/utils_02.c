/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 04:38:03 by alee              #+#    #+#             */
/*   Updated: 2022/05/16 04:44:16 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"

void	ft_set_status(t_shell_data *p_data, t_shell_status status)
{
	p_data->status = status;
	return ;
}
