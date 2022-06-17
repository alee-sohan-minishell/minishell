/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_tree_utils.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 23:07:08 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/18 04:47:20 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_TREE_UTILS_H
# define SHELL_TREE_UTILS_H
# include "../tree/shell_tree.h"
# include "../tree/shell_heredoc.h"
# include "../tree/shell_tree_utils.h"

void	shell_tree_init(t_shell_tree_node *node);
void	shell_heredoc_init(t_shell_heredoc_node *node);
int		shell_tree_push(t_shell_tree_node **p_focus, t_shell_tree_node *item);
int		shell_tree_insert_push_child(t_shell_tree_node **p_focus,
				t_shell_tree_node *item, int push_left, int append_left);
int		shell_tree_insert_push_focus(t_shell_tree_node **p_focus, t_shell_tree_node *item, int left);

#endif
