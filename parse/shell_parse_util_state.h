/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_util_state.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:40:49 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/20 21:57:04 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_PARSE_UTIL_STATE_H
# define SHELL_PARSE_UTIL_STATE_H

# include "shell_parse_state.h"

t_state_shell_parse	shell_parse_util_get_state(char c);

#endif
