/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_utils2.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:34:47 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/12 10:58:29 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_PARSE_UTILS2_H
# define SHELL_PARSE_UTILS2_H

# include "../parse/shell_parse_utils1.h"

void	shell_parse_util_env_init(t_parse_node *node);
int		shell_parse_util_env_add_char(t_parse_node *node, char c);
char	*shell_parse_util_env_to_str(t_parse_node *node);
int		shell_parse_util_is_cmd_end(t_state_shell_parse state);
int		shell_parse_util_free_argv(char **argv);

#endif
