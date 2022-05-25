/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 04:30:37 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 18:28:46 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_INIT_H
# define SHELL_INIT_H
# include "../shell/shell.h"

void	shell_init(t_shell_data *p_data, int argc, char **argv[], char **env[]);
int		arg_init(t_shell_data *p_data, int argc, char **env[]);
int		isatty_init(t_shell_data *p_data);
int		dup_init(t_shell_data *p_data);
int		env_init(t_shell_data *p_data, char **env[]);

#endif
