#ifndef _BIN_TREE_
# define _BIN_TREE_
#include "../shell/shell.h"

typedef struct s_tree_type
{
	t_shell_tree_node *p_root_node;
} t_tree;

t_tree		*make_tree(t_shell_tree_node root_node);
t_shell_tree_node	*get_root_node_BT(t_tree *p_tree);
t_shell_tree_node	*insert_leftchild_node_BT(t_shell_tree_node *p_parent_node, t_shell_tree_node element);
t_shell_tree_node	*insert_rightchild_node_BT(t_shell_tree_node *p_parent_node, t_shell_tree_node element);
t_shell_tree_node	*get_leftchild_node_BT(t_shell_tree_node *p_node);
t_shell_tree_node	*get_rightchild_node_BT(t_shell_tree_node *p_node);
void		delete_tree(t_tree *p_tree);
void		delete_tree_node(t_shell_tree_node *p_node);

#endif
