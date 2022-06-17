/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:56:31 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/18 06:22:38 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell_tree.h"
#include "../parse/shell_parse_utils1.h"

// 그냥 매개변수 값 가지고 있는 트리 노드 만들어서 리턴
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

// focus가 바뀌어야 해서 double pointer
// 따로 검사하는 건 없는데 줄 수 줄이기 위해서 int 반환, 무조건 성공해서 0을 return
int	tree_append(t_shell_tree_node **p_focus, t_shell_tree_node *item)
{
	if (NULL == (*p_focus)->left)
		(*p_focus)->left = item;
	else if (NULL == (*p_focus)->right)
		(*p_focus)->right = item;
	item->parent = (*p_focus);
	if (T_COMMAND != item->kind) // command의 경우는 focus 그대로 (짚어넣고 focus올라감)
		(*p_focus) = item;
	return (0);
}

// ls -l < test.txt -a 같이 redirect 후 argv 나오는 경우
// redirect tree_node 밑에 가장 첫 번째 오른쪽 command tree_node 찾아서 argv 넣어줌
void	tree_find_append_argv(t_shell_tree_node *focus, char **argv)
{
	focus = focus->left; // 시작은 redirect 일테니 그 왼쪽 자식부터 시작
	// parsing 하면서 redirect 왔다가 string 오는 상황에서만 함수 호출하므로
	// 오른쪽 자식만 찾았을 때 command node가 없는 경우 없음
	while (T_COMMAND != focus->kind)
		focus = focus->right;
	//# 4. 찾은 command node의 오른쪽 argv에 넣어줘야 하는데, 이 함수 매개변수 argv로 받는게 맞나? char로 받아야 하는 거 아니려나 고민 중
	// 일단 state 만들면서 생각해야 할 듯
	// TODO
}

// tree 따로 검사하는 건 없는데 줄 수 줄이기 위해서, 무조건 성공해서 0 반환
int	tree_delete(t_shell_tree_node *tree)
{
	int		cnt;
	char	**argv;

	if (tree->argv)
	{
		argv = tree->argv;
		cnt = -1;
		while (argv[++cnt])
			free(argv[cnt]);
		free(argv);
	}
	if (tree->filepath)
		free(tree->filepath);
	if (tree->left)
		tree_delete(tree->left);
	free(tree->left);
	if (tree->right)
		tree_delete(tree->right);
	free(tree->right);
}

int	is_redirect(t_shell_tree_kind kind)
{
	if (S_P_REDIRECT_IN == kind || S_P_REDIRECT_OUT == kind
		|| S_P_REDIRECT_HEREDOC == kind || S_P_REDIRECT_APPEND == kind)
		return (1);
	return (0);
}
