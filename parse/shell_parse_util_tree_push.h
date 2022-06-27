/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_util_tree_push.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:34:47 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/27 21:47:50 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_PARSE_UTIL_TREE_PUSH_H
# define SHELL_PARSE_UTIL_TREE_PUSH_H

# include "../tree_heredoc/shell_tree.h"

int		is_full(t_shell_tree_node *focus);
int		is_left(t_shell_tree_node *focus);
int		is_bool(t_shell_tree_kind kind);
void	shell_parse_util_push_replace(t_shell_tree_node **p_focus,
			t_shell_tree_node *item);
void	shell_parse_util_push_chld(t_shell_tree_node **p_f,
			t_shell_tree_node *item);

#endif
