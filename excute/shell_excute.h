/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_excute.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:09:42 by alee              #+#    #+#             */
/*   Updated: 2022/06/28 00:24:50 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_EXCUTE_H
# define SHELL_EXCUTE_H
# include "../shell/shell.h"

void	shell_execute_tree(t_shell_data *p_data);
void	shell_execute(t_shell_data *p_data);

#endif
