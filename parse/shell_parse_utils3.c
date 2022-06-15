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

int	shell_parse_util_env_convert(t_shell_data *p_data)
{
	t_env_node			*env_node;
	char				*key;
	int					cnt;

	key = shell_parse_util_env_to_str(&p_data->parse_env);
	if (NULL == key)
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
		if (shell_parse_util_add_char(&p_data->parse_list, env_node->value[cnt]))
			return (-1);
	return (0);
}
