/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_utils3.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:34:47 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/12 10:58:29 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_PARSE_UTILS3_H
# define SHELL_PARSE_UTILS3_H

# include "../shell/shell.h"
# include "../parse/shell_parse_state.h"

t_state_shell_parse	shell_parse_util_get_state(char c);
int					shell_parse_util_insert_cmd(t_shell_data *p_data);
int					shell_parse_util_env_convert(t_shell_data *p_data);

#endif
