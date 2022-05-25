/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:38:42 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 18:38:43 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init/shell_init.h"
#include "../signal/signal.h"
#include "../libft/libft.h"
#include "../utils/error_msg_utils_01.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "../init/shell_utils_01.h"
#include "../env/env_list_interface_01.h"

static char	**get_path_list(t_env_list *p_list)
{
	t_env_node	*cur_node;
	char 		**path_list;
	char		*temp;
	int			index;
	
	index = 0;
	if (env_node_search(p_list, "PATH", &cur_node) == 0)
		return (NULL);
	path_list = ft_split(cur_node->value, ':');
	if (!path_list)
		exit(1);
	while (path_list[index])
	{
		temp = path_list[index];
		path_list[index] = ft_strjoin(path_list[index], "/");
		if (!path_list[index])
			exit (1);
		free(temp);
		++index;
	}
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
			exit (1);
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

int	ft_exec_command(t_shell_data *p_data)
{
	pid_t	pid;
	char	**path_list;
	int		index;
	int		status;

	index = 0;
	set_signal_foreground();
	path_list = get_path_list(&p_data->env_list);
	if (!path_list)
	{
		ft_custom_perror_param(NULL, p_data->cmd[0], strerror(2));
		return (127);
	}
	path_list = get_exec_path(p_data, path_list);
	while (path_list[index])
	{
		pid = fork();
		if (pid == 0)
		{
			set_tc_attr_to_default(p_data);
			if (execve(path_list[index], p_data->cmd, NULL) == -1)
				exit(42);
		}
		wait(&status);
		if (status >> 8 != 42)
			break ;
		++index;
	}
	if (!path_list[index])
	{
		ft_custom_perror_param(NULL, p_data->cmd[0], "command not found");
		free_array(path_list);
		return (127);
	}
	free_array(path_list);
	return ((128 + (status & 0x7f)) * ((status & 0x7f) != 0) + (status >> 8));
}
