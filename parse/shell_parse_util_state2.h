/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_util_state2.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:40:49 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/26 21:14:04 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_PARSE_UTIL_STATE2_H
# define SHELL_PARSE_UTIL_STATE2_H

# include "shell_parse_state.h"

t_state_shell_parse	treat_first_redirect_env(t_shell_data *p_data, char c);
t_state_shell_parse	treat_first_redirect_dquote_env(t_shell_data *p_data,
						char c);
t_state_shell_parse	treat_first_redirect_string_env(t_shell_data *p_data,
						char c);
t_state_shell_parse	treat_first_redirect_string_dquote_env(t_shell_data *p_data,
						char c);
char				**append_argv(char **argv, char *arg);

#endif
