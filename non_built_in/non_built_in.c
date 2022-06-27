/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:38:42 by alee              #+#    #+#             */
/*   Updated: 2022/06/27 13:33:55 by alee             ###   ########.fr       */
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
#define WRITE 1
#define READ 0

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
	//int		status;
	struct stat	s;

	index = 0;
	set_signal_foreground();
	path_list = get_path_list(&p_data->env_list);
	if (ft_strchr(p_data->cmd[0], '/') != NULL || !path_list)
	{
		pid = fork();
		if (pid > 0)
		{	
			signal(SIGINT, SIG_IGN);
			p_data->global_data.pipe_pid[p_data->cmd_count] = pid;
		}
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
		//wait(&status);
		//p_data->term_status = (128 + (status & 0x7f)) * ((status & 0x7f) != 0) + (status >> 8);
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
			if (pid > 0)
			{
				p_data->global_data.pipe_pid[p_data->cmd_count] = pid;
				if (p_data->is_piped)
				{
					if (p_data->cmd_count < p_data->pipe_count)
					{
						close(p_data->pipe_fd[p_data->cmd_count][WRITE]);
						dup2(p_data->pipe_fd[p_data->cmd_count][READ], STDIN_FILENO);
						close(p_data->pipe_fd[p_data->cmd_count][READ]);
					}
					else
					{
						dup2(p_data->fd_in_old, STDIN_FILENO);
						close(p_data->fd_in_old);
					}
				}
			}
			else if (pid == 0)
			{
				set_tc_attr_to_default(p_data);
				if (p_data->is_piped)
				{
					if (p_data->cmd_count < p_data->pipe_count)
					{
						for (int i = 0; i < p_data->cmd_count - 1; i++)
						{
							close(p_data->pipe_fd[i][READ]);
							close(p_data->pipe_fd[i][WRITE]);
						}
						
						close(p_data->pipe_fd[p_data->cmd_count][READ]);
						if (!p_data->fd_out_new)
							dup2(p_data->pipe_fd[p_data->cmd_count][WRITE], STDOUT_FILENO);	
						close(p_data->pipe_fd[p_data->cmd_count][WRITE]);
						for (int i = p_data->cmd_count + 1; i < p_data->pipe_count; i++)
						{
							close(p_data->pipe_fd[i][READ]);
							close(p_data->pipe_fd[i][WRITE]);
						}
					}
					else
					{
						dup2(p_data->fd_out_old, STDOUT_FILENO);
						close(p_data->fd_out_old);
					}
				}
				if (p_data->is_fileio_success)
					execve(path_list[index], p_data->cmd, *p_data->p_env);
				else
					exit(p_data->fileio_errno);
			}
			//wait(&status);
			//p_data->term_status = (128 + (status & 0x7f)) * ((status & 0x7f) != 0) + (status >> 8);
			break ;
		}
		++index;
	}
	if (!path_list[index])
	{
		ft_self_perror_param(NULL, p_data->cmd[0], "command not found");
		p_data->global_data.pipe_status[p_data->cmd_count] = 127;
		p_data->last_status = 127;
	}
	free_array(path_list);
	return (0);
}
