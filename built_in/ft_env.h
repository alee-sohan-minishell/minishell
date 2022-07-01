/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan<sohan@student.42seoul.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:14:35 by sohan             #+#    #+#             */
/*   Updated: 2022/05/25 04:38:23 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENV_H
# define FT_ENV_H
# include "../shell/shell.h"

int		ft_env(char **cmd, t_shell_data *p_data);
void	print_env(t_env_list *p_list);

#endif
