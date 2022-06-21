/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_util_tree.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 23:07:09 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/20 22:24:22 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "../tree_heredoc/shell_tree.h"
#include "shell_parse_util_node_list.h"
#include "shell_parse_state.h"

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
}

int	shell_parse_util_insert_redirect(t_shell_data *p_data)
{
	char				*str;
	t_shell_tree_node	*tree_node;

	str = shell_parse_node_to_str(p_data->parse_tmp);
	if (NULL == str)
		return (-1);
	tree_node = tree_new_node(p_data->kind, NULL, -1, str); // str의 포인터가 그대로 filepath로 들어가기 때문에 str free 해주면 안됨
	if (NULL == tree_node)
		return (-1);
	shell_parse_util_push_tree(&p_data->focus, tree_node);
	return (0);
}

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
	if (T_ROOT == (*p_focus)->kind)
		push_left = 0;
	if (T_PIPE == item->kind)
		append_left = 0;
	if (T_ROOT == (*p_focus)->kind || // root인 경우나
		(shell_parse_util_is_redirect((*p_focus)->kind)
		&& shell_parse_util_is_redirect(item->kind))) // focus, item 둘 다 redirect인 경우 자식을 민다
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
}
