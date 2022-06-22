/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_util_tree.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 23:07:09 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/22 23:39:12 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "../tree_heredoc/shell_tree.h"
#include "shell_parse_util_node_list.h"
#include "shell_parse_state.h"
#include "shell_parse_util_tree_push.h"

int	shell_parse_util_is_redirect(t_shell_tree_kind kind)
{
	if (S_P_REDIRECT_IN == kind || S_P_REDIRECT_OUT == kind
		|| S_P_REDIRECT_HEREDOC == kind || S_P_REDIRECT_APPEND == kind
		|| S_P_REDIRECT_ENV == kind || S_P_REDIRECT_QUOTE == kind
		|| S_P_REDIRECT_DQUOTE == kind || S_P_REDIRECT_DQUOTE_ENV == kind)
		return (1);
	return (0);
}

// focus가 바뀌어야 해서 double pointer
void	shell_parse_util_push_tree(t_shell_tree_node **p_focus,
				t_shell_tree_node *item)
{
	int	push_left;
	int	append_left;

	// shell_tree_init에서 구조체의 지역변수 tree_node의 주소를 p_data->focus로 주기 때문에
	// p_focus가 NULL인 경우는 없음
	push_left = 1;
	append_left = 1;
	if (T_EMPTY == (*p_focus)->kind
		&& (T_PIPE == item->kind || shell_parse_util_is_redirect(item->kind)
		|| T_BOOL_AND == item->kind || T_BOOL_OR == item->kind))
		return (shell_parse_util_push_replace(p_focus, item));
	else if (is_child_full(*p_focus)
		|| (shell_parse_util_is_redirect((*p_focus)->kind) && (*p_focus)->left
		&& !shell_parse_util_is_redirect(item->kind)))
		return (shell_parse_util_push_focus(p_focus, item));
	shell_parse_util_push_chld(p_focus, item);

/*
	if (T_EMPTY == (*p_focus)->kind
		&& (T_PIPE == item->kind || shell_parse_util_is_redirect(item->kind)
		|| T_BOOL_AND == item->kind || T_BOOL_OR == item->kind))
	{
		(*p_focus)->kind = item->kind;
		(*p_focus)->argv = item->argv;
		(*p_focus)->fd = item->fd;
		(*p_focus)->filepath = item->filepath;
		return (tree_free(item, 0));
	}
	else if (T_ROOT == (*p_focus)->kind
		|| ((*p_focus)->left && NULL == (*p_focus)->right
		&& (T_EMPTY == (*p_focus)->kind || T_PIPE == (*p_focus)->kind
		|| (shell_parse_util_is_redirect((*p_focus)->kind) && T_PIPE == item->kind))))
		push_left = 0;
	else if ((*p_focus)->left && (*p_focus)->right
		&& (T_PIPE == (*p_focus)->kind || T_BOOL_AND == (*p_focus)->kind
		|| T_BOOL_OR == (*p_focus)->kind))
		push_left = 0;
	if (T_PIPE == item->kind)
		append_left = 0;
	if ((((*p_focus)->left && (*p_focus)->right) && (T_PIPE == (*p_focus)->kind
		|| T_BOOL_AND == (*p_focus)->kind || T_BOOL_OR == (*p_focus)->kind
		|| T_EMPTY == (*p_focus)->kind))
		|| (shell_parse_util_is_redirect((*p_focus)->kind)
		&& (*p_focus)->left && 0 == shell_parse_util_is_redirect(item->kind)))
		shell_tree_insert_push_focus(p_focus, item, push_left);
	else
		shell_tree_insert_push_child(p_focus, item, push_left, append_left);
		*/
}

int	shell_parse_util_insert_cmd(t_shell_data *p_data)
{
	char				**argv;
	t_shell_tree_node	*tree_node;

	argv = shell_parse_list_to_argv(&p_data->parse_list);
	if (NULL == argv)
		return (-1);
	tree_node = tree_new_node(T_COMMAND, argv, -1, NULL); // argv의 포인터가 그대로 들어가기 때문에 argv free 해주면 안됨
	if (NULL == tree_node)
	{
		shell_parse_util_argv_free(argv, -1);
		return (-1);
	}
	shell_parse_util_push_tree(&p_data->focus, tree_node);
	return (0);
}

int	shell_parse_util_insert_redirect(t_shell_data *p_data)
{
	char				*str;
	t_shell_tree_node	*tree_node;

	str = shell_parse_node_to_str(p_data->parse_tmp);
	if (NULL == str)
		return (-1);
	p_data->parse_tmp = shell_parse_new_node();
	if (NULL == p_data->parse_tmp)
		return (-1);
	tree_node = tree_new_node(p_data->redirect_kind, NULL, -1, str); // str의 포인터가 그대로 filepath로 들어가기 때문에 str free 해주면 안됨
	if (NULL == tree_node)
		return (-1);
	shell_parse_util_push_tree(&p_data->focus, tree_node);
	return (0);
}

// ls -l < test.txt -a 같이 redirect 후 argv 나오는 경우
// redirect tree_node 밑에 가장 첫 번째 오른쪽 command tree_node 찾아서 argv 넣어줌
int	shell_parse_util_insert_argv_in_cmd(t_shell_tree_node *focus, char *str)
{
	// parsing 하면서 redirect 왔다가 string 오는 상황에서만 함수 호출하므로
	// 오른쪽 자식만 찾았을 때 command node가 없는 경우 없음
	focus = focus->left; // 시작은 redirect 일테니 그 왼쪽 자식부터 시작
	while (T_COMMAND != focus->kind)
	{
		if (focus->right)
			focus = focus->right;
		else
			focus = focus->left;
	}

	//# TODO 2. 매개변수 argv로 받아야 하는지 str로 받아야 하는지 모르겠다.
	// 찾은 command node의 오른쪽 argv에 넣어줘야 함
	str = NULL;
	return (0);
}
