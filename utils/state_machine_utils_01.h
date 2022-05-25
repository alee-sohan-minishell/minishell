/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_utils_01.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 04:37:45 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 04:14:23 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_MACHINE_UTILS_01_H
# define STATE_MACHINE_UTILS_01_H
# include "../shell/shell.h"

void	ft_set_status(t_shell_data *p_data, t_shell_status status);
int		status_close(t_shell_data *p_data);

#endif
