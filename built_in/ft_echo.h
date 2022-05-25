/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:05:55 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 15:25:03 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ECHO_H
# define FT_ECHO_H
# include "../shell/shell.h"

int		ft_echo(char **cmd, t_shell_data *p_data);
int		is_newline_flag(char **cmd);
int		is_continuous_opt_value(const char *line, char opt_flag, \
														char opt_value);
int		is_hashtag_flag(const char *line);
void	print_echo(char *line, t_shell_data *p_data);

#endif
