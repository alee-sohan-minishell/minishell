/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_util_state.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:56:51 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/20 21:59:06 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_PARSE_UTIL_STATE_H
# define SHELL_PARSE_UTIL_STATE_H

# include "shell_parse_state.h"

t_state_shell_parse	shell_parse_util_get_state(char c);
int					shell_parse_util_is_redirect(t_shell_tree_kind kind);

#endif
