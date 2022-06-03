#include "bintree.h"
#include <stdlib.h>
#include <stdio.h>

t_tree	*make_tree(t_tree_node root_node)
{
	t_tree *p_tree;

	p_tree = (t_tree *)malloc(sizeof(t_tree));
	if (p_tree == NULL)
		return (NULL);
	p_tree->p_root_node = (t_tree_node*)malloc(sizeof(t_tree_node));
	if (p_tree->p_root_node == NULL)
		return (NULL);
	*(p_tree->p_root_node) = root_node;
	p_tree->p_root_node->p_left_child = NULL;
	p_tree->p_root_node->p_right_child = NULL;
	return (p_tree);
}

t_tree_node	*get_root_node_BT(t_tree* p_tree)
{
	return (p_tree->p_root_node);
}

t_tree_node *insert_leftchild_node_BT(t_tree_node *p_parent_node, t_tree_node element)
{
	t_tree_node *lChild;

	lChild = (t_tree_node *)malloc(sizeof(t_tree_node));
	if (lChild == NULL || p_parent_node == NULL)
		return (NULL);
	p_parent_node->p_left_child = lChild;
	*(p_parent_node->p_left_child) = element;
	p_parent_node->p_left_child->p_left_child = NULL;
	p_parent_node->p_left_child->p_right_child = NULL;
	return (p_parent_node);
}

t_tree_node	*insert_rightchild_node_BT(t_tree_node *p_parent_node, t_tree_node element)
{
	t_tree_node	*rChild;

	rChild	= (t_tree_node *)malloc(sizeof(t_tree_node));
	if	(rChild == NULL || p_parent_node == NULL)
		return	(NULL);
	p_parent_node->p_right_child	= rChild;
	*(p_parent_node->p_right_child)	= element;
	p_parent_node->p_right_child->p_left_child	= NULL;
	p_parent_node->p_right_child->p_right_child	= NULL;
	return	(p_parent_node);
}

t_tree_node	*get_leftchild_node_BT(t_tree_node *p_node)
{
	if	(p_node == NULL)
		return	(NULL);
	return	(p_node->p_left_child);
}

t_tree_node	*get_rightchild_node_BT(t_tree_node *p_node)
{
	 if (p_node == NULL)
		return	(NULL);
	return	(p_node->p_right_child);	
}

void	delete_tree_node(t_tree_node	*p_node)
{
	if	(p_node != NULL)
	{
		delete_tree_node(p_node->p_left_child);
		delete_tree_node(p_node->p_right_child);
		printf("%c	free\n", p_node->data);
		free(p_node);
		p_node	= NULL;
	}
}

void	delete_tree(t_tree* p_tree) // 이진 트리 삭제
{
	t_tree_node	*temp;

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

void	pre_order(t_tree_node *p_node) // v - l - r
{
	if (p_node != NULL)
	{
		printf("%c ", p_node->data);
		pre_order(p_node->p_left_child);
		pre_order(p_node->p_right_child);
	}
}

void	in_order(t_tree_node *p_node) // l - v - r
{
	if (p_node != NULL)
	{
		in_order(p_node->p_left_child);
		printf("%c ", p_node->data);
		in_order(p_node->p_right_child);
	}
}

void	post_order(t_tree_node *p_node) // l - r - v
{
	if (p_node != NULL)
	{
		post_order(p_node->p_left_child);
		post_order(p_node->p_right_child);
		printf("%c ", p_node->data);
	}
}

/*int main(void) 
{
	t_tree *p_tree;
	t_tree_node root_node;
	t_tree_node newNode[12];
	t_tree_node *temp;
	t_tree_node *temp1;
	
	root_node.data = 'A';
	p_tree = make_tree(root_node);
	temp = p_tree->p_root_node;

	for (int i = 0; i < 12; i++)
		newNode[i].data = 'B' + i;

	temp = insert_leftchild_node_BT(temp, newNode[0]); // B
	temp = insert_rightchild_node_BT(temp, newNode[1]); // C
	printf("\t\t\t\t\t\t%c\t\t\t\t\t\t\tlevel 1\n", p_tree->p_root_node->data);
	printf("\t\t\t\t\n");
	printf("\t\t\t%c\t\t\t", p_tree->p_root_node->p_left_child->data);
	printf("\t\t\t%c\t\t\t\tlevel 2\n", p_tree->p_root_node->p_right_child->data);
	printf("\t\t\t\t\n");
	
	temp = get_leftchild_node_BT(temp);
	temp = insert_leftchild_node_BT(temp, newNode[2]);
	temp = insert_rightchild_node_BT(temp, newNode[3]);

	// printf("Parent: %c\n", temp->data);
	printf("\t\t%c\t", temp->p_left_child->data);
	printf("\t%c\t", temp->p_right_child->data);

	temp = get_root_node_BT(p_tree); 
	temp = get_rightchild_node_BT(temp);
	temp = insert_leftchild_node_BT(temp, newNode[4]);
	temp = insert_rightchild_node_BT(temp, newNode[5]);

	// printf("Parent: %c\n", temp->data);
	printf("\t\t\t%c\t", temp->p_left_child->data);
	printf("\t%c\t\t\tlevel 3\n", temp->p_right_child->data);
	printf("\n");
	
	temp = get_root_node_BT(p_tree);
	// printf("I'm roooot : %c\n", temp->data);
	
	temp = get_leftchild_node_BT(temp);
	temp = get_leftchild_node_BT(temp);
	temp = insert_leftchild_node_BT(temp, newNode[6]);
	temp = insert_rightchild_node_BT(temp, newNode[7]);

	// printf("Parent: %c\n", temp->data);
	printf("\t%c\t", temp->p_left_child->data); // H
	printf("  %c", temp->p_right_child->data); // I

	temp = get_root_node_BT(p_tree);
	temp = get_leftchild_node_BT(temp); 
	temp = get_rightchild_node_BT(temp);
	temp = insert_leftchild_node_BT(temp, newNode[8]);
	
	// printf("\nParent: %c\n", temp->data);
	printf("\t  %c ", temp->p_left_child->data); // J
	//printf("Right: %c\n", temp->p_right_child->data);
	
	temp = get_root_node_BT(p_tree);
	// printf("I'm roooot : %c\n", temp->data);
	
	temp = get_rightchild_node_BT(temp);
	temp = get_leftchild_node_BT(temp);
	temp = insert_rightchild_node_BT(temp, newNode[9]);

	// printf("Parent: %c\n", temp->data);
	//printf("Left: %c\n", temp->p_left_child->data);
	printf("\t\t\t\t  %c", temp->p_right_child->data);
	
	temp = get_root_node_BT(p_tree);
	temp = get_rightchild_node_BT(temp);
	temp = get_rightchild_node_BT(temp);
	temp = insert_leftchild_node_BT(temp, newNode[10]);
	temp = insert_rightchild_node_BT(temp, newNode[11]);
	
	// printf("Parent: %c\n", temp->data);
	printf("\t  %c ", temp->p_left_child->data);
	printf("\t%c\t\tlevel 4\n", temp->p_right_child->data);

	temp = get_root_node_BT(p_tree);
	printf("\nI'm roooot : %c\n", temp->data);

	printf("\n+++++ Tree Traversal +++++\n");

	printf("\n====== preOrder ======\n");
	preOrder(temp);
	printf("\n======================\n");

	printf("\n====== inOrder ======\n");
	inOrder(temp);
	printf("\n======================\n");

	printf("\n====== postOrder ======\n");
	postOrder(temp);	
	printf("\n======================\n");

	printf("\n+++++ Delete Tree +++++\n");
	delete_tree(p_tree);
	
	return 0;
}*/
