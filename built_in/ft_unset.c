/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 01:02:20 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 21:03:37 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env_list.h"
#include "../built_in/ft_exit.h"
#include "../env/env_list_interface_02.h"
#include "../libft/libft.h"
#include <unistd.h>
#include "../utils/command_utils_01.h"
#include "../utils/error_msg_utils_01.h"
#include "../utils/string_utils_01.h"

int	ft_unset(char **cmd, t_env_list *p_list)
{
	int	idx;
	int	ret;

	if (!cmd || !(*cmd) || !p_list)
		return (1);
	idx = 1;
	ret = 0;
	while (idx < get_cmd_count(cmd))
	{
		if (is_variable_rule(cmd[idx][0]) == 0)
			ft_self_perror_param("unset", cmd[idx], "not a valid identifier");
		if (env_node_delete(p_list, cmd[idx]) == 0)
			ret = 1;
		idx++;
	}
	return (ret);
}
