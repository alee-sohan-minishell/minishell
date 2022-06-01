/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:34:06 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/12 11:09:20 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "../parse/shell_parse_utils1.h"
#include "../parse/shell_parse_utils2.h"
#include "../tree/shell_tree.h"
#include "../tree/shell_tree_utils.h"

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
