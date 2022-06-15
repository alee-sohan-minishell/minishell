/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:34:06 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/12 11:09:20 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../shell/shell.h"
#include "../parse/shell_parse_utils1.h"
#include "../parse/shell_parse_utils2.h"
#include "../libft/libft.h"
#include "../parse/shell_parse_state.h"
#include "../tree/shell_tree.h"
#include "../tree/shell_tree_utils.h"

void	shell_parse_util_env_init(t_parse_node *node)
{
	node->cnt = 0;
	node->size = 0;
	node->str = NULL;
	node->next = NULL; // env는 node 하나만 써서 사실이건 사용 안 한다고 보면 됨
}

int	shell_parse_util_env_add_char(t_parse_node *node, char c)
{
	char	*ret;

	// t_shell 구조체에서 지역 변수로 node 선언하고, 그 주소 받아오기 때문에
	// node 가 NULL인 경우는 없음
	if (NULL == node->str)
	{
		node->str = malloc(sizeof(char) * SHELL_PARSE_NODE_SIZE);
		if (NULL == node->str)
			return (-1);
		node->size = SHELL_PARSE_NODE_SIZE;
	}
	if (node->cnt == node->size)
	{
		ret = malloc(sizeof(char) * node->size * 2);
		if (NULL == ret)
			return (-1);
		ft_memcopy(ret, node->str, node->size);
		free(node->str);
		node->str = ret;
		node->size *= 2;
	}
	node->str[node->cnt++] = c;
}


// env_node에 담아둔 것은 정확한 크기를 모르고 malloc 한 거라
// parsing 다 돼서 정확한 크기를 알 수 있어, str으로 다시 깔끔하게 만듬
char	*shell_parse_util_env_to_str(t_parse_node *node)
{
	char	*ret;

	ret = malloc(sizeof(char) * node->cnt + 1);
	if (NULL == ret)
		return (NULL);
	ret[node->cnt] = '\0';
	ft_memcopy(ret, node->str, node->cnt);
	free(node->str);
	return (ret);
}

// 에러나는 상황에서만 이전 것 free하는 용도로 쓰이기 때문에
// 항상 -1인 S_P_ERROR를 리턴
int	shell_parse_util_free_argv(char **argv)
{
	int	cnt;

	cnt = -1;
	while (argv[++cnt])
		free(argv[cnt]);
	free(argv);
	return (-1);
}

int	shell_parse_util_insert_cmd(t_shell_data *p_data)
{
	char				**argv;
	t_shell_tree_node	*tree_node;

	argv = shell_parse_util_list_to_argv(&p_data->parse_list);
	if (NULL == argv)
		return (-1);
	tree_node = tree_new_node(T_COMMAND, argv, 0, NULL);
	if (NULL == tree_node)
		return (shell_parse_util_free_argv(argv)); // 무조건 -1 리턴
	tree_insert(&p_data->focus, tree_node);
	if (tree_make_cmd_child(tree_node)) // 실패해도 tree는 parse_state_error에서 재귀적으로 지움
		return (shell_parse_util_free_argv(argv)); // 무조건 -1 리턴
}
