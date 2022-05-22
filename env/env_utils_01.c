/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 16:01:17 by alee              #+#    #+#             */
/*   Updated: 2022/05/22 18:55:41 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../shell/shell.h"

int	is_env_form(char **env[])
{
	int	idx;

	idx = 0;
	while ((*env)[idx])
	{
		if (ft_strchr((*env)[idx], '=') == (char *)0)
			return (0);
		idx++;
	}
	return (1);
}

int	env_create(t_shell_data *p_data, char **env[])
{
	int	idx;
	if(p_data)
		return (0);
	idx = 0;
	while ((*env)[idx])
	{
		// if (env_node_add_back(&p_data->env_list, env_create_node
		idx++;
	}
	return (1);
}

int	env_parse(t_shell_data *p_data, char **env[])
{
	int			idx[3];

	idx[0] = 0;
	while ((*env)[idx[0]])
	{
		idx[2] = ft_strlen(ft_strchr((*env)[idx[0]], '=') + 1);
		idx[1] = ft_strlen((*env)[idx[0]]) - (1 + idx[2]);
		idx[0]++;
	}
	if (!p_data)
		return (0);
	return (1);
}
