/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan<sohan@student.42seoul.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 02:03:55 by sohan             #+#    #+#             */
/*   Updated: 2022/05/28 04:26:24 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H
# include "../shell/shell.h"

int	redirection_in(t_shell_data *p_data, const char *file);
int	redirection_out(t_shell_data *p_data, const char *file);
int	redirection_append(t_shell_data *p_data, const char *file);

#endif
