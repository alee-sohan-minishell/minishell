/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bintree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 22:23:51 by alee              #+#    #+#             */
/*   Updated: 2022/06/23 22:25:20 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINTREE_H
# define BINTREE_H
# include "../shell/shell.h"

typedef struct s_tree_type
{
	t_shell_tree_node	*p_root_node;
}	t_tree;

t_tree				*make_tree(t_shell_tree_node root_node);
t_shell_tree_node	*get_root_node_BT(t_tree *p_tree);
t_shell_tree_node	*insert_leftchild_node_BT(t_shell_tree_node *p_parent_node, \
													t_shell_tree_node element);
t_shell_tree_node	*insert_rightchild_node_BT(t_shell_tree_node *p_parent_node, \
													t_shell_tree_node element);
t_shell_tree_node	*get_leftchild_node_BT(t_shell_tree_node *p_node);
t_shell_tree_node	*get_rightchild_node_BT(t_shell_tree_node *p_node);
void		delete_tree(t_tree *p_tree);
void		delete_tree_node(t_shell_tree_node *p_node);

#endif
