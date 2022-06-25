/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_util_tree2.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:34:47 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/25 23:20:22 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_PARSE_UTIL_TREE2_H
# define SHELL_PARSE_UTIL_TREE2_H

# include "../shell/shell.h"
# include "../tree_heredoc/shell_tree.h"

t_state_shell_parse	get_redirect_state(t_shell_tree_kind kind);
int					insert_heredoc_node(t_shell_data *p_data, char *str);
char				*make_heredoc_filename(int *cnt);

#endif
