/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_check_tree.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 22:54:22 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/29 20:26:02 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_PARSE_CHECK_TREE_H
# define SHELL_PARSE_CHECK_TREE_H

# include "../tree_heredoc/shell_tree.h"

int					shell_parse_check_tree(t_shell_tree_node *t);
t_state_shell_parse	return_redirect_env(t_shell_data *p_data, char c);

#endif
