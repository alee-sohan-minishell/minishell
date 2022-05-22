/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 16:01:17 by alee              #+#    #+#             */
/*   Updated: 2022/05/22 21:44:35 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../shell/shell.h"
#include "../env/env_list_interface.h"

int	is_env_form(char **env[], int *env_count)
{
	int	idx;

	idx = 0;
	while ((*env)[idx])
	{
		if (ft_strchr((*env)[idx], '=') == (char *)0)
			return (0);
		idx++;
	}
	if (!env_count)
		*env_count = idx;
	else
		return (0);
	return (1);
}

int	env_set(t_shell_data *p_data, int env_count, char **env[])
{
	int			idx;
	if (p_data || !env)
		return (1);
	idx = 0;
	while (idx < env_count)
	{
		if (env_node_add_back(&p_data->env_list, env_node_create()) == 0)
			return (env_node_clear(&p_data->env_list));

		idx++;
	}
	return (1);
}
