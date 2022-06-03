#include "excute/bintree.h"
#include "libft/libft.h"
#include "init/shell_init.h"
#include "excute/shell_excute.h"
#include <stdlib.h>
#include <stdio.h>

t_tree	*make_tree(t_shell_tree_node root_node)
{
	t_tree *p_tree;

	p_tree = (t_tree *)malloc(sizeof(t_tree));
	if (p_tree == NULL)
		return (NULL);
	p_tree->p_root_node = (t_shell_tree_node*)malloc(sizeof(t_shell_tree_node));
	if (p_tree->p_root_node == NULL)
		return (NULL);
	*(p_tree->p_root_node) = root_node;
	p_tree->p_root_node->left = NULL;
	p_tree->p_root_node->right = NULL;
	return (p_tree);
}

t_shell_tree_node	*get_root_node_BT(t_tree* p_tree)
{
	return (p_tree->p_root_node);
}

t_shell_tree_node *insert_leftchild_node_BT(t_shell_tree_node *p_parent_node, t_shell_tree_node element)
{
	t_shell_tree_node *lChild;

	lChild = (t_shell_tree_node *)malloc(sizeof(t_shell_tree_node));
	if (lChild == NULL || p_parent_node == NULL)
		return (NULL);
	p_parent_node->left = lChild;
	*(p_parent_node->left) = element;
	p_parent_node->left->left = NULL;
	p_parent_node->left->right = NULL;
	return (p_parent_node);
}

t_shell_tree_node	*insert_rightchild_node_BT(t_shell_tree_node *p_parent_node, t_shell_tree_node element)
{
	t_shell_tree_node	*rChild;

	rChild	= (t_shell_tree_node *)malloc(sizeof(t_shell_tree_node));
	if	(rChild == NULL || p_parent_node == NULL)
		return	(NULL);
	p_parent_node->right	= rChild;
	*(p_parent_node->right)	= element;
	p_parent_node->right->left	= NULL;
	p_parent_node->right->right	= NULL;
	return	(p_parent_node);
}

t_shell_tree_node	*get_leftchild_node_BT(t_shell_tree_node *p_node)
{
	if	(p_node == NULL)
		return	(NULL);
	return	(p_node->left);
}

t_shell_tree_node	*get_rightchild_node_BT(t_shell_tree_node *p_node)
{
	 if (p_node == NULL)
		return	(NULL);
	return	(p_node->right);	
}

void	delete_tree_node(t_shell_tree_node	*p_node)
{
	if	(p_node != NULL)
	{
		delete_tree_node(p_node->left);
		delete_tree_node(p_node->right);
		printf("%d	free\n", p_node->kind);
		free(p_node);
		p_node	= NULL;
	}
}

void	delete_tree(t_tree* p_tree) // 이진 트리 삭제
{
	t_shell_tree_node	*temp;

	temp	= p_tree->p_root_node;
	if	(p_tree == NULL)
	{
		printf("This	tree is NULL");
		return	;
	}
	delete_tree_node(temp);
	free(p_tree);
	p_tree	= NULL;
}

/*void	pre_order(t_shell_tree_node *p_node) // v - l - r
{
	if (p_node != NULL)
	{
		printf("%c ", p_node->data);
		pre_order(p_node->left);
		pre_order(p_node->right);
	}
}

void	in_order(t_shell_tree_node *p_node) // l - v - r
{
	if (p_node != NULL)
	{
		in_order(p_node->left);
		printf("%c ", p_node->data);
		in_order(p_node->right);
	}
}

void	post_order(t_shell_tree_node *p_node) // l - r - v
{
	if (p_node != NULL)
	{
		post_order(p_node->left);
		post_order(p_node->right);
		printf("%c ", p_node->data);
	}
}*/

int main(int argc, char **argv, char **env) 
{
	t_shell_data	shell;
	t_tree *p_tree;
	t_shell_tree_node root_node;
	t_shell_tree_node newNode[3];
	t_shell_tree_node *temp;
	//t_shell_tree_node *temp1;
	char	*tmp_argv[2];
	

	ft_bzero(&shell, sizeof(shell));
	shell_init(&shell, argc, &argv, &env);
	shell.is_piped = 0;
	root_node.kind = 0;
	p_tree = make_tree(root_node);
	temp = p_tree->p_root_node;
	//cat > ls
	newNode[0].kind = T_REDIRECT_OUT;
	newNode[0].filepath = "ls";

	newNode[1].kind = T_COMMAND;
	tmp_argv[0] = "cat";
	tmp_argv[1] = NULL;
	//tmp_argv[2] = NULL;
	newNode[1].argv = tmp_argv;

	temp = insert_rightchild_node_BT(temp, newNode[0]); // C
	printf("\nI'm roooot? : %d\n", temp->kind);
	temp = get_rightchild_node_BT(temp);
	temp = insert_leftchild_node_BT(temp, newNode[1]);
	temp = get_root_node_BT(p_tree);

	printf("\n+++++ Tree Traversal +++++\n");
	shell.cmd_tree = p_tree->p_root_node;
	shell_execute_tree(&shell);

	printf("\n+++++ Delete Tree +++++\n");
	delete_tree(p_tree);
	

	root_node.kind = 0;
	p_tree = make_tree(root_node);
	temp = p_tree->p_root_node;

	//cat | cat
	newNode[0].kind = T_PIPE;
	newNode[1].kind = T_COMMAND;
	newNode[2].kind = T_COMMAND;
	tmp_argv[0] = "cat";
	tmp_argv[1] = NULL;
	newNode[1].argv = tmp_argv;
	newNode[2].argv = tmp_argv;

	temp = insert_rightchild_node_BT(temp, newNode[0]);
	temp = get_rightchild_node_BT(temp);
	temp = insert_leftchild_node_BT(temp, newNode[1]);
	temp = insert_rightchild_node_BT(temp, newNode[2]);

	temp = get_root_node_BT(p_tree);
	printf("\n+++++ Tree Traversal +++++\n");
	shell.cmd_tree = p_tree->p_root_node;
	shell.is_piped = 0;
	shell_execute_tree(&shell);
	printf("\n+++++ Delete Tree +++++\n");
	delete_tree(p_tree);

	root_node.kind = 0;
	p_tree = make_tree(root_node);
	temp = p_tree->p_root_node;

	//cat | ls
	newNode[0].kind = T_PIPE;
	newNode[1].kind = T_COMMAND;
	newNode[2].kind = T_COMMAND;
	tmp_argv[0] = "cat";
	tmp_argv[1] = NULL;
	newNode[1].argv = tmp_argv;
	tmp_argv[0] = "ls";
	tmp_argv[1] = NULL;
	newNode[2].argv = tmp_argv;

	temp = insert_rightchild_node_BT(temp, newNode[0]);
	temp = get_rightchild_node_BT(temp);
	temp = insert_leftchild_node_BT(temp, newNode[1]);
	temp = insert_rightchild_node_BT(temp, newNode[2]);

	temp = get_root_node_BT(p_tree);
	printf("\n+++++ Tree Traversal +++++\n");
	shell.cmd_tree = p_tree->p_root_node;
	shell.is_piped = 0;
	shell_execute_tree(&shell);
	printf("\n+++++ Delete Tree +++++\n");
	delete_tree(p_tree);

	return 0;
}
