/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_util_tree.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 23:07:09 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/26 15:55:07 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "../tree_heredoc/shell_tree.h"
#include "shell_parse_util_node_list.h"
#include "shell_parse_state.h"
#include "shell_parse_util_tree_push.h"
#include "shell_parse_util_tree2.h"

int	is_redirect(t_shell_tree_kind kind)
{
	if (T_REDIRECT_IN == kind || T_REDIRECT_OUT == kind
		|| T_REDIRECT_HEREDOC == kind || T_REDIRECT_APPEND == kind)
		return (1);
	return (0);
}

// focus가 바뀌어야 해서 double pointer
void	shell_parse_util_push_tree(t_shell_tree_node **p_f,
				t_shell_tree_node *item)
{
	// shell_tree_init에서 구조체의 지역변수 tree_node의 주소를 p_data->focus로 주기 때문에
	// p_f가 NULL인 경우는 없음
	if (T_EMPTY == (*p_f)->kind
		&& !(T_EMPTY == item->kind || T_COMMAND == item->kind))
		return (shell_parse_util_push_replace(p_f, item));
	else if ((T_EMPTY == (*p_f)->kind && is_full(*p_f))
		|| (T_PIPE == (*p_f)->kind && is_full(*p_f) && !is_redirect(item->kind))
		|| (is_bool((*p_f)->kind) && is_full(*p_f) && T_PIPE != item->kind)
		|| (is_redirect((*p_f)->kind) && !(*p_f)->left && !(*p_f)->right && T_PIPE == item->kind)
		|| (is_redirect((*p_f)->kind) && (*p_f)->left && !is_redirect(item->kind)))
		return (shell_tree_insert_push_focus(p_f, item, 1));
	shell_parse_util_push_chld(p_f, item);
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
	tree_node->cmdnum = p_data->cmd_count;
	shell_parse_util_push_tree(&p_data->focus, tree_node);
	++p_data->cmd_count;
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
	if (T_REDIRECT_HEREDOC == p_data->redirect_kind)
	{
		if (insert_heredoc_node(p_data, str)) // str의 포인터가 그대로 delimiter로 들어가기 때문에 str free 해주면 안됨
			return (-1);
		str = make_heredoc_filename(&p_data->heredoc_cnt);
		if (NULL == str)
			return (-1);
	}
	tree_node = tree_new_node(p_data->redirect_kind, NULL, -1, str);
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
