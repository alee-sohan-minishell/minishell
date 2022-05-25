/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg_utils_01.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 03:03:32 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 18:33:18 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MSG_UTILS_01_H
# define ERROR_MSG_UTILS_01_H

void	ft_perror(const char *msg);
void	ft_perror_param(const char *pre_cmd, const char *param, int errno_flag);
void	ft_self_perror_param(const char *pre_cmd, \
									const char *param, const char *err_msg);
void	ft_perror_exit(const char *msg, int exit_status);
int		ft_msg_return(const char *msg, int return_value, int std_type);
void	ft_msg_exit(const char *msg, int exit_status, int std_type);
int		ft_perror_param_len(const char *pre_cmd, const char *param);

#endif
