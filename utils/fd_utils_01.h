/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils_01.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 03:01:28 by alee              #+#    #+#             */
/*   Updated: 2022/06/21 14:11:38 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FD_UTILS_01_H
# define FD_UTILS_01_H
# include "../shell/shell.h"

int		ft_dup(int fd);
int		ft_dup2(int fd1, int fd2);
int		ft_close(int fd);
void	recover_default_fd(t_shell_data *p_data);

#endif
