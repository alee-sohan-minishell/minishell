/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_non_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan<sohan@student.42seoul.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 08:48:36 by sohan             #+#    #+#             */
/*   Updated: 2022/06/29 18:26:51 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "non_built_in.h"
#include "../libft/libft.h"
#include "../env/env_list_interface_01.h"
#include "../utils/error_msg_utils_02.h"

static void	*free_empty_list(char **path_list)
{
	free(path_list);
	return (NULL);
}

static char	**get_path_list(t_env_list *p_list)
{
	t_env_node	*cur_node;
	char		**path_list;
	char		*temp;
	int			index;

	index = 0;
	if (env_node_search(p_list, "PATH", &cur_node) == 0)
		return (NULL);
	path_list = ft_split(cur_node->value, ':');
	if (!path_list)
		ft_self_perror_param_exit(NULL, "get_path_list()", \
										"Error while malloc\n", 1);
	while (path_list[index])
	{
		temp = path_list[index];
		path_list[index] = ft_strjoin(path_list[index], "/");
		if (!path_list[index])
			ft_self_perror_param_exit(NULL, "get_path_list()", \
											"Error while malloc\n", 1);
		free(temp);
		++index;
	}
	if (index == 0)
		return (free_empty_list(path_list));
	return (path_list);
}

static char	**get_exec_path(t_shell_data *p_data, char **path_list)
{
	char		*temp;
	int			index;

	index = 0;
	while (path_list[index])
	{
		temp = path_list[index];
		path_list[index] = ft_strjoin(path_list[index], p_data->cmd[0]);
		if (!path_list[index])
			ft_self_perror_param_exit(NULL, "get_exec_list()", \
											"Error while malloc\n", 1);
		free(temp);
		++index;
	}
	return (path_list);
}

static void	free_array(char **array)
{
	int	index;

	index = 0;
	while (array[index])
	{
		free(array[index]);
		++index;
	}
	free(array);
}

void	ft_non_built_in(t_shell_data *p_data)
{
	char	**path_list;

	path_list = get_path_list(&p_data->env_list);
	if (ft_strchr(p_data->cmd[0], '/') != NULL || !path_list)
	{
		direct_execute(p_data);
		if (path_list)
			free_array(path_list);
		return ;
	}
	path_list = get_exec_path(p_data, path_list);
	search_execute(p_data, path_list);
	free_array(path_list);
	return ;
}
