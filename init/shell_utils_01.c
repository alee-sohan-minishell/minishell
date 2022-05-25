/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:21:26 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 18:23:53 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include <unistd.h>
#include "../utils/state_machine_utils_01.h"

int	set_tc_attr(t_shell_data *p_data)
{
	if (tcgetattr(STDOUT_FILENO, &p_data->default_term_attr) == 0)
	{
		p_data->new_term_attr = p_data->default_term_attr;
		p_data->new_term_attr.c_lflag &= (~ECHOCTL);
		tcsetattr(STDOUT_FILENO, TCSANOW, &p_data->new_term_attr);
	}
	else
	{
		ft_set_status(p_data, S_ERROR);
		return (-1);
	}
	return (1);
}

int	set_tc_attr_to_default(t_shell_data *p_data)
{
	tcsetattr(STDOUT_FILENO, TCSANOW, &p_data->default_term_attr);
	return (0);
}
