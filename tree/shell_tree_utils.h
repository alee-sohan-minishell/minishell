/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_tree_utils.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 23:07:08 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/11 20:36:44 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_TREE_UTILS_H
# define SHELL_TREE_UTILS_H
# include "../tree/shell_tree.h"
# include "../tree/shell_heredoc.h"
# include "../tree/shell_tree_utils.h"

void	shell_tree_init(t_shell_tree_node *node);
void	shell_heredoc_init(t_shell_heredoc_node *node);
int		tree_make_cmd_child(t_shell_tree_node *node);

#endif
