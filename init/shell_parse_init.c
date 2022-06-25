/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:19:56 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/25 23:16:32 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "../tree_heredoc/shell_tree.h"
#include "../tree_heredoc/shell_heredoc.h"
#include "../parse/shell_parse_node_list.h"

// 더미라서 init에서 한 번 초기화
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

// 더미라서 init에서 한 번 초기화
void	shell_heredoc_init(t_shell_heredoc_list *list)
{
	list->cnt = 0;
	list->head.pre = NULL;
	list->head.next = &list->tail;
	list->head.delimiter = NULL;
	list->tail.pre = &list->head;
	list->tail.next = NULL;
	list->tail.delimiter = NULL;
}

// 더미라서 init에서 한 번 초기화
void	shell_list_init(t_parse_list *list)
{
	list->cnt = 0;
	list->head.size = 0;
	list->head.cnt = 0;
	list->head.str = NULL;
	list->head.pre = NULL;
	list->head.next = &list->tail;
	list->tail.size = 0;
	list->tail.cnt = 0;
	list->tail.str = NULL;
	list->tail.pre = &list->head;
	list->tail.next = NULL;
}

int	shell_parse_init(t_shell_data *p_data)
{
	shell_tree_init(&p_data->tree);
	p_data->focus = &p_data->tree;
	shell_heredoc_init(&p_data->heredoc_list);
	p_data->heredoc_cnt = 0;
	shell_list_init(&p_data->parse_list);
	p_data->parse_tmp = shell_parse_new_node();
	if (NULL == p_data->parse_tmp)
		return (-1);
	p_data->parse_env = shell_parse_new_node();
	if (NULL == p_data->parse_env)
		return (-1);
	p_data->redirect_kind = T_EMPTY;
	return (0);
}
