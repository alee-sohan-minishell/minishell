/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils_01.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan<sohan@student.42seoul.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 03:01:28 by sohan             #+#    #+#             */
/*   Updated: 2022/06/22 17:09:00 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FD_UTILS_01_H
# define FD_UTILS_01_H

int	ft_dup(int fd);
int	ft_dup2(int fd1, int fd2);
int	ft_close(int fd);
int	ft_pipe(int *fildes);

#endif
