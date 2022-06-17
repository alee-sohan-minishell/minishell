/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_tree_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 23:07:09 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/18 06:27:57 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../shell/shell.h"
#include "../tree/shell_tree.h"
#include "../tree/shell_heredoc.h"
#include "../libft/libft.h"

void	shell_tree_init(t_shell_tree_node *node)
{
	node->kind = T_ROOT;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->argv = NULL;
	node->fd = -1;
	node->filepath = NULL;
}

void	shell_heredoc_init(t_shell_heredoc_node *node)
{
	node->next = NULL;
	node->delimiter = NULL;
}

// focus가 바뀌어야 해서 double pointer
// tree 따로 검사하는 건 없는데 줄 수 줄이기 위해서 return int, 무조건 성공해서 0을 반환함
int	shell_tree_push(t_shell_tree_node **p_focus, t_shell_tree_node *item)
{
	int	push_left;
	int	append_left;

	// shell_tree_init에서 구조체의 지역변수 tree_node의 주소를 p_data->focus로 주기 때문에
	// p_focus가 NULL인 경우는 없음
	push_left = 1;
	append_left = 1;
	if (T_ROOT == (*p_focus)->kind)
		push_left = 0;
	if (T_PIPE == item->kind)
		append_left = 0;
	if (T_ROOT == (*p_focus)->kind || // root인 경우나
		(is_redirect((*p_focus)->kind) && is_redirect(item->kind))) // focus, item 둘 다 redirect인 경우 자식을 민다
		return (shell_tree_insert_push_child(p_focus, item, push_left, append_left));
	else if (T_COMMAND == item->kind)
		return (tree_append(p_focus, item));
	else if (T_EMPTY == (*p_focus)->kind)
	{
		(*p_focus)->kind = item->kind;
		(*p_focus)->argv = item->argv;
		(*p_focus)->fd = item->fd;
		(*p_focus)->filepath = item->filepath;
		return (tree_delete(item));
	}
	else if ((*p_focus)->left && (*p_focus)->right) // 자식 꽉 찬 경우 focus를 민다
		return (shell_tree_insert_push_focus(p_focus, item, push_left));
	return (tree_append((*p_focus), item));
}

int	shell_tree_insert_push_child(t_shell_tree_node **p_focus,
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
	return (0); // 무조건 성공
}

int	shell_tree_insert_push_focus(t_shell_tree_node **p_focus, t_shell_tree_node *item, int left)
{
	if (left) // focus를 item의 왼쪽으로 밀어야 하는 경우
		item->left = *p_focus;
	else
		item->right = *p_focus;
	// TODO focus가 NULL인 경우 터짐
	if ((*p_focus)->parent->left == (*p_focus)) // focus가 왼쪽 자식이었던 경우
		(*p_focus)->parent->left =	item;
	else
		(*p_focus)->parent->right =	item;
	item->parent = (*p_focus)->parent;
	(*p_focus)->parent = item;
	(*p_focus) = item; // 방금 짚어넣은 아이템으로 포커스 이동
	return (0); // 무조건 성공
}
