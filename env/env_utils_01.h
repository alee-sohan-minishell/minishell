/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_01.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan<sohan@student.42seoul.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 16:01:02 by sohan             #+#    #+#             */
/*   Updated: 2022/05/25 12:50:54 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_UTILS_01_H
# define ENV_UTILS_01_H
# include "../shell/shell.h"

int		is_env_form(char **env[], int *env_count);
int		env_set(t_shell_data *p_data, int env_count, char **env[]);
int		is_default_home(t_env_list *p_list, char **o_default_home);

#endif
