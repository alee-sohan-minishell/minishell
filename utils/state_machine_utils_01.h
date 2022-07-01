/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine_utils_01.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan<sohan@student.42seoul.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 04:37:45 by sohan             #+#    #+#             */
/*   Updated: 2022/05/25 04:14:23 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_MACHINE_UTILS_01_H
# define STATE_MACHINE_UTILS_01_H
# include "../shell/shell.h"

void	ft_set_status(t_shell_data *p_data, t_shell_status status);
int		status_close(t_shell_data *p_data);

#endif
