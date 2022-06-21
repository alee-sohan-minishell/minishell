/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:56:31 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/21 16:02:35 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell_tree.h"

t_shell_tree_node	*tree_new_node(t_shell_tree_kind kind, char **argv, int fd,
						char *filepath)
{
	t_shell_tree_node	*node;

	node = malloc(sizeof(t_shell_tree_node));
	if (NULL == node)
		return (NULL);
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->kind = kind;
	node->argv = argv;
	node->fd = fd;
	node->filepath = filepath;
	return (node);
}

// tree root가 dummy인 걸 고려한 free
void	tree_free(t_shell_tree_node *tree)
{
	int		cnt;

	if (tree->argv)
	{
		cnt = -1;
		while (tree->argv[++cnt])
			free(tree->argv[cnt]);
		free(tree->argv);
	}
	if (tree->filepath)
		free(tree->filepath);
	if (tree->left)
		tree_free(tree->left);
	free(tree->left);
	tree->left = NULL;
	if (tree->right)
		tree_free(tree->right);
	free(tree->right);
	tree->right = NULL;
}

// focus가 바뀌어야 해서 double pointer
void	tree_append(t_shell_tree_node **p_focus, t_shell_tree_node *item)
{
	if (NULL == (*p_focus)->left)
		(*p_focus)->left = item;
	else if (NULL == (*p_focus)->right)
		(*p_focus)->right = item;
	item->parent = (*p_focus);
	if (T_COMMAND != item->kind) // command의 경우는 focus 그대로 (짚어넣고 focus 올라간다고도 할 수 있음)
		(*p_focus) = item;
}

void	shell_tree_insert_push_child(t_shell_tree_node **p_focus,
			t_shell_tree_node *item, int push_left, int append_left)
{
	if (push_left) // focus의 왼쪽 자식을 밀어내는 경우
	{
		item->right = (*p_focus)->left;
		if (append_left)
			item->left = (*p_focus)->left;
		(*p_focus)->left = item;
	}
	else
	{
		item->right = (*p_focus)->right;
		if (append_left)
			item->left = (*p_focus)->right;
		(*p_focus)->right = item;
	}
	if (append_left && item->left)
		item->left->parent = item;
	else if (append_left && item->right)
		item->right->parent = item;
	item->parent = *p_focus;
	(*p_focus) = item; // 방금 짚어넣은 아이템으로 포커스 이동
}

void	shell_tree_insert_push_focus(t_shell_tree_node **p_focus,
			t_shell_tree_node *item, int push_left)
{
	if (push_left) // focus를 item의 왼쪽으로 밀어야 하는 경우
		item->left = *p_focus;
	else
		item->right = *p_focus;
	// focus tree dummy header 가리킨 상태로 시작하고, close state에서 tree node의 parent 없으면 focus 위로 안 올라가기 때문에 NULL인 경우 없음
	if ((*p_focus)->parent->left == (*p_focus)) // focus가 왼쪽 자식이었던 경우
		(*p_focus)->parent->left =	item;
	else
		(*p_focus)->parent->right =	item;
	item->parent = (*p_focus)->parent;
	(*p_focus)->parent = item;
	(*p_focus) = item; // 방금 짚어넣은 아이템으로 포커스 이동
}
