/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:38:42 by alee              #+#    #+#             */
/*   Updated: 2022/06/17 17:43:00 by alee             ###   ########.fr       */
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
#include <signal.h>
#include <sys/stat.h>

//debug
#include <stdio.h>


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
	struct stat	s;

	index = 0;
	set_signal_foreground();
	path_list = get_path_list(&p_data->env_list);
	if (ft_strchr(p_data->cmd[0], '/') != NULL || !path_list)
	{
		pid = fork();
		if (pid > 0)
			signal(SIGINT, SIG_IGN);
		else if (pid == 0)
		{
			set_tc_attr_to_default(p_data);
			if (execve(p_data->cmd[0], p_data->cmd, *p_data->p_env) == -1)
			{
				if (errno == ENOEXEC)//이짓까지 해야될까?
				{
					char	*cmd[3];

					cmd[0] = "/bin/sh";
					cmd[1] = p_data->cmd[0];
					cmd[2] = NULL;
					set_tc_attr_to_default(p_data);
					execve("/bin/sh", cmd, NULL);
				}
				if (errno != 2 && errno != 13)
				{
					ft_self_perror_param(NULL, p_data->cmd[0], strerror(errno));
					exit(126);
				}
				else if (errno == 13)
				{
					if (stat(p_data->cmd[0], &s) == -1 || s.st_mode & S_IFREG)
						ft_self_perror_param(NULL, p_data->cmd[0], strerror(errno));
					else
						ft_self_perror_param(NULL, p_data->cmd[0], "is a directory");
					exit(126);
				}
				else
				{
					ft_self_perror_param(NULL, p_data->cmd[0], strerror(errno));
					exit(127);
				}
			}
		}
		wait(&status);
		p_data->term_status = (128 + (status & 0x7f)) * ((status & 0x7f) != 0) + (status >> 8);
		if (path_list)
			free_array(path_list);
		return (0);
	}
	path_list = get_exec_path(p_data, path_list);
	while (path_list[index])
	{
		if (stat(path_list[index], &s) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				set_tc_attr_to_default(p_data);
				execve(path_list[index], p_data->cmd, *p_data->p_env);
			}
			wait(&status);
			p_data->term_status = (128 + (status & 0x7f)) * ((status & 0x7f) != 0) + (status >> 8);
			break ;
		}
		++index;
	}
	if (!path_list[index])
	{
		ft_self_perror_param(NULL, p_data->cmd[0], "command not found");
		p_data->term_status = 127;
	}
	free_array(path_list);
	return (0);
}
