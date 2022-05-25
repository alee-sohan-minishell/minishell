/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 16:01:17 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 04:23:57 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../shell/shell.h"
#include "../env/env_list_interface_01.h"

int	is_env_form(char **env[], int *env_count)
{
	int	idx;

	idx = 0;
	while ((*env)[idx])
	{
		if (ft_strchr((*env)[idx], '=') == (char *)0)
			return (-1);
		idx++;
	}
	if (env_count)
		*env_count = idx;
	else
		return (-1);
	return (1);
}

int	env_set(t_shell_data *p_data, int env_count, char **env[])
{
	int			idx;
	int			vk[2];

	idx = 0;
	env_list_init(&p_data->env_list);
	while (idx < env_count)
	{
		vk[0] = ft_strlen((*env)[idx]) - ft_strlen(ft_strchr((*env)[idx], '='));
		vk[1] = ft_strlen((*env)[idx]) - (vk[0] + 1);
		if (env_node_add_back(&p_data->env_list, \
		env_node_create(ft_strndup((*env)[idx], vk[0]), \
		ft_strndup(ft_strchr((*env)[idx], '=') + 1, vk[1]))) == 0)
			return (env_node_clear(&p_data->env_list));
		idx++;
	}
	return (1);
}

int	is_default_home(t_env_list *p_list, char **o_default_home)
{
	t_env_node	*node;

	if (!p_list || !o_default_home)
		return (-1);
	if (env_node_search(p_list, "HOME", &node) == 0)
		return (-1);
	*o_default_home = ft_strdup(node->value);
	if (!(*o_default_home))
		return (-1);
	return (1);
}

/*char	*get_current_home(t_shell_data *p_data)
{

	return (NULL);
}*/
