/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:07:44 by alee              #+#    #+#             */
/*   Updated: 2022/06/27 22:55:26 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_PARSE_H
# define SHELL_PARSE_H

# include "../shell/shell.h"
# include "shell_parse_state.h"

void	shell_parse_free(t_shell_data *p_data);
int		shell_parse_check(t_shell_data *p_data, t_state_shell_parse state,
			char **ret);
int		shell_parse_check_not_interpret(char *str);
char	*loop_parse(t_shell_data *p_data, t_state_shell_parse *state,
			char *str);
void	shell_parse(t_shell_data *p_data);

#endif
