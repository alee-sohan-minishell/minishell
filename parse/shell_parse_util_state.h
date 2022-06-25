/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_util_state.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:40:49 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/25 18:05:35 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_PARSE_UTIL_STATE_H
# define SHELL_PARSE_UTIL_STATE_H

# include "shell_parse_state.h"

t_state_shell_parse	shell_parse_util_get_state(char c);
int					is_redirect_state(t_state_shell_parse state);
int					add_char_exit_code(t_shell_data *p_data);
t_state_shell_parse	treat_first_env(t_state_shell_parse state,
						t_shell_data *p_data, char c);
t_state_shell_parse	treat_first_dquote_env(t_state_shell_parse state,
						t_shell_data *p_data, char c);

#endif
