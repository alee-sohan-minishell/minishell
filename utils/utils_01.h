/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_01.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 07:49:27 by alee              #+#    #+#             */
/*   Updated: 2022/05/16 04:38:16 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_01_H
# define UTILS_01_H

int		ft_dup(int fd);
int		ft_close(int fd);
void	ft_perror(const char *msg);
void	ft_perror_exit(const char *msg, int exit_status);


#endif
