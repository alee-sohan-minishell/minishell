/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_tree_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 23:07:09 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/08 23:20:22 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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

// 이미 커맨드 노드에 argv랑 filename 들어가 있으므로, 자식 2개는 그냥 더미노드
int	tree_make_cmd_child(t_shell_tree_node *node)
{
	t_shell_tree_node	*dummy;

	dummy = tree_new_node(T_STRING, NULL, 0, NULL);
	if (NULL == dummy)
		return (-1);
	node->left = dummy; // TODO 어차피 error 처리에서 재귀적으로 free하므로 여기서 안 함
	dummy = tree_new_node(T_STRING, NULL, 0, NULL);
	if (NULL == dummy)
		return (-1);
	node->right = dummy;
	return (0);
}
