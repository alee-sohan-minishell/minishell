/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:12:03 by sohan             #+#    #+#             */
/*   Updated: 2022/06/29 18:27:50 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

void	no_foreground_process(void);
void	shell_command_is_foreground_process(void);
void	executable_file_is_foreground_process(void);
void	minishell_is_foreground_process(void);

#endif
