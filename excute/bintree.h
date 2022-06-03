#ifndef _BIN_TREE_
# define _BIN_TREE_

typedef struct s_tree_node_type
{
	char					data;
	struct s_tree_node_type *p_left_child;
	struct s_tree_node_type *p_right_child;
} t_tree_node;

typedef struct s_tree_type
{
	struct s_tree_node_type *p_root_node;
} t_tree;

t_tree		*make_tree(t_tree_node root_node);
t_tree_node	*get_root_node_BT(t_tree *p_tree);
t_tree_node	*insert_leftchild_node_BT(t_tree_node *p_parent_node, t_tree_node element);
t_tree_node	*insert_rightchild_node_BT(t_tree_node *p_parent_node, t_tree_node element);
t_tree_node	*get_leftchild_node_BT(t_tree_node *p_node);
t_tree_node	*get_rightchild_node_BT(t_tree_node *p_node);
void		delete_tree(t_tree *p_tree);
void		delete_tree_node(t_tree_node *p_node);

#endif

#ifndef _COMMON_TREE_DEF_
# define _COMMON_TREE_DEF_

# define TRUE		1
# define FALSE		0

#endif
