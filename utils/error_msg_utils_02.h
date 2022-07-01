/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg_utils_02.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan<sohan@student.42seoul.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:15:54 by sohan             #+#    #+#             */
/*   Updated: 2022/06/23 21:38:07 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MSG_UTILS_02_H
# define ERROR_MSG_UTILS_02_H

void	ft_msg_exit(const char *msg, int exit_status, int std_type);
int		ft_perror_param_len(const char *pre_cmd, const char *param);
void	ft_self_perror_param_exit(const char *pre_cmd, \
					const char *param, const char *err_msg, int exit_status);

#endif
