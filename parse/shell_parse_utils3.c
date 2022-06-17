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

#include <stdlib.h>
#include "../parse/shell_parse_utils1.h"
#include "../parse/shell_parse_utils2.h"
#include "../env/env_list.h"
#include "../env/env_list_interface_01.h"
#include "../utils/error_msg_utils_01.h"

t_state_shell_parse	shell_parse_util_get_state(char c)
{
	int			cnt;
	const char	str[] = {' ', '\'', '"', '$',
		'(', ')', '&', '|', '<', '>'};

	cnt = -1;
	while (++cnt < 10) // 10개 중에 매칭되는 상태 리턴
		if (str[cnt] == c)
			return (cnt);
	return (S_P_STRING); // 그게 아니면 string임
}

int	shell_parse_util_insert_cmd(t_shell_data *p_data)
{
	char				**argv;
	t_shell_tree_node	*tree_node;

	argv = shell_parse_util_list_to_argv(&p_data->parse_list);
	if (NULL == argv)
		return (-1);
	tree_node = tree_new_node(T_COMMAND, argv, 0, NULL); // argv의 포인터가 그대로 들어가기 때문에 argv free 해주면 안됨
	if (NULL == tree_node)
		return (shell_parse_util_free_argv(argv, -1)); // 무조건 -1 리턴
	shell_tree_push(&p_data->focus, tree_node);
}

int	shell_parse_util_env_convert(t_shell_data *p_data) //# -1. TODO 이거 마지막으로 util 체크해야 함, util 적절한지 다시 고민해보자 졸려서 제대로 못봤을 수 있음, 이거 끝나고 state에서 util 사용하는 거 이상없나 체크
{
	t_env_node	*env_node;
	char		*key;
	int			cnt;

	key = shell_parse_util_node_to_str(&p_data->parse_env);
	if (NULL == key)
		return (-1);
	p_data->parse_env = shell_parse_util_new_node();
	if (NULL == p_data->parse_env)
		return (-1);
	if (env_node_search(&p_data->env_list, key, &env_node) == 0)
	{
		ft_perror_param("env", key, 0);
		free(key);
		return (-1);
	}
	free(key);
	cnt = -1;
	while (env_node->value[++cnt])
		if (shell_parse_util_add_char_node(&p_data->parse_list,
				env_node->value[cnt]))
			return (-1);
	return (0);
}
