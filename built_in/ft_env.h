/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:14:35 by alee              #+#    #+#             */
/*   Updated: 2022/05/23 18:20:56 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENV_H
# define FT_ENV_H
# include "../shell/shell.h"

int		ft_env(char **cmd, t_shell_data *p_data);
void	print_env(char **cmd, t_env_list *p_list);

#endif
