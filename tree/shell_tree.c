/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:56:31 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/01 21:15:52 by min-jo           ###   ########.fr       */
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
	node->fd = 0;
	node->filepath = filepath;
	return (node);
}

void	tree_insert(t_shell_tree_node **focus, t_shell_tree_node *item)
{
	if (NULL == *focus)
		*focus = item;
	else if (T_EMPTY == (*focus)->kind)
	{
		(*focus)->kind = item->kind;
		(*focus)->argv = item->argv;
		(*focus)->fd = item->fd;
		(*focus)->filepath = item->filepath;
		tree_delete(item);
	}
	else if (NULL == (*focus)->left || NULL == (*focus)->right)
		tree_append(focus, item);
	else
	{
		if (T_PIPE == item->kind)
			item->right = focus;
		else
			item->left = focus;
		item->parent = (*focus)->parent;
		(*focus)->parent = item;
	}
}

void	tree_append(t_shell_tree_node **focus, t_shell_tree_node *item)
{
	if (NULL == (*focus)->left)
		(*focus)->left = item;
	else if (NULL == (*focus)->right)
		(*focus)->right = item;
	item->parent = focus;
}

void	tree_delete(t_shell_tree_node *tree)
{
	int		cnt;
	char	**argv;

	if (tree->argv)
	{
		argv = tree->argv;
		cnt = 0;
		while (argv[cnt])
		{
			free(argv[cnt]);
			++cnt;
		}
		free(argv);
	}
	if (tree->filepath)
		free(tree->filepath);
	if (tree->left)
		tree_delete(tree->left);
	if (tree->right)
		tree_delete(tree->right);
}
