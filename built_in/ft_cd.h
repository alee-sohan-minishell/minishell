/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:56:59 by alee              #+#    #+#             */
/*   Updated: 2022/06/28 03:49:51 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CD_H
# define FT_CD_H
# include "../shell/shell.h"

int		ft_cd(char **cmd, t_shell_data *p_data);
int		is_chdir_home(char **cmd, char **o_home_path, t_shell_data *p_data);
int		cd_err_msg(char **cmd, char *home_path);
void	set_default_path(t_shell_data *p_data, char **o_home_path, \
										t_env_node *home_node);

#endif
