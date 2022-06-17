/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:07:44 by alee              #+#    #+#             */
/*   Updated: 2022/06/17 21:18:23 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_PARSE_H
# define SHELL_PARSE_H
# include "../shell/shell.h"

void	shell_parse_error(); // TODO
void	shell_parse_check(); // TODO
int		shell_parse_check_not_interpret(char *str);
void	loop_parse(t_shell_data *p_data, t_state_shell_parse *state, char *str);
void	shell_parse(t_shell_data *p_data);

#endif
