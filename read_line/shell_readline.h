/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_readline.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 05:39:13 by alee              #+#    #+#             */
/*   Updated: 2022/05/20 09:58:40 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_READLINE_H
# define SHELL_READLINE_H
# include "../shell/shell.h"

void	shell_readline(t_shell_data *p_data);
void	insert_cmd_history(const char *cmd);

#endif
