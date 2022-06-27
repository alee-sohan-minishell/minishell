/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_execute_tree.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 00:15:36 by alee              #+#    #+#             */
/*   Updated: 2022/06/28 01:18:01 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "../utils/state_machine_utils_01.h"
#include "../built_in/ft_cd.h"
#include "../built_in/ft_pwd.h"
#include "../built_in/ft_echo.h"
#include "../built_in/ft_exit.h"
#include "../built_in/ft_env.h"
#include "../built_in/ft_unset.h"
#include "../built_in/ft_export.h"
#include "../non_built_in/non_built_in.h"
#include "../init/shell_utils_01.h"
#include "../redirection/redirection.h"
#include "../excute/shell_excute.h"
#include "../init/shell_parse_init.h"
#include "../parse/shell_parse.h"
#include <unistd.h>
#include <stdlib.h>
#include "../heredoc/heredoc.h"

void	set_pipe(t_shell_data *p_data)
{
	--p_data->pipe_num;
	if (pipe(p_data->pipe_fd[p_data->pipe_num]) == -1)
		fprintf(stderr,"pipe error\n");
	p_data->is_piped = 1;
}

int	set_fd(t_shell_data *p_data, t_shell_tree_node *cmd_tree)
{
	if (cmd_tree->kind == T_REDIRECT_HEREDOC)
	{
		if (heredoc(p_data, cmd_tree->filepath) == -1)
		{
			p_data->is_fileio_success = 0;
			return (-1);
		}
		p_data->is_fileio_success = 1;
	}
	else if (cmd_tree->kind == T_REDIRECT_IN)
	{
		if (redirection_in(p_data, cmd_tree->filepath) == -1)
		{
			p_data->is_fileio_success = 0;
			return (-1);
		}
		p_data->is_fileio_success = 1;
	}
	else if (cmd_tree->kind == T_REDIRECT_OUT)
	{
		if (redirection_out(p_data, cmd_tree->filepath) == -1)
		{
			p_data->is_fileio_success = 0;
			return (-1);
		}
		p_data->is_fileio_success = 1;
	}
	else if (cmd_tree->kind == T_REDIRECT_APPEND)
	{
		if (redirection_append(p_data, cmd_tree->filepath) == -1)
		{
			p_data->is_fileio_success = 0;
			return (-1);
		}
		p_data->is_fileio_success = 1;
	}
	return (0);
}

void	tree_traverse_set_pipe(t_shell_data *p_data, t_shell_tree_node *cmd_tree)
{
	if (cmd_tree)
	{
		if (cmd_tree->kind == T_PIPE)
			set_pipe(p_data);
		tree_traverse_set_pipe(p_data, cmd_tree->left);
		tree_traverse_set_pipe(p_data, cmd_tree->right);
	}
}

void	tree_traverse_exe_cmd(t_shell_data *p_data, t_shell_tree_node *cmd_tree)
{
	pid_t	pid;

	if (cmd_tree)
	{
		if (p_data->is_fileio_success)
			set_fd(p_data, cmd_tree);
		if (!cmd_tree->left && !cmd_tree->right)
		{
			if (p_data->is_piped)
			{
				pid = fork();
				if (pid > 0)
				{
					p_data->global_data.pipe_pid[p_data->cmd_count] = pid;
					if (p_data->cmd_count < p_data->pipe_count)
					{
						close(p_data->pipe_fd[p_data->cmd_count][WRITE]);
						dup2(p_data->pipe_fd[p_data->cmd_count][READ], STDIN_FILENO);
						close(p_data->pipe_fd[p_data->cmd_count][READ]);
					}
					else
					{
						if (!p_data->fd_in_new)
						{
							dup2(p_data->fd_in_old, STDIN_FILENO);
							close(p_data->fd_in_old);
						}
					}
				}
				else if (pid == 0)
				{
					set_tc_attr_to_default(p_data);
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
							if (!p_data->fd_out_new)
							{
								dup2(p_data->fd_out_old, STDOUT_FILENO);
								close(p_data->fd_out_old);
							}
						}
					if (cmd_tree->kind == T_COMMAND)
					{
						p_data->cmd = cmd_tree->argv;
						shell_execute(p_data);
					}
					exit(p_data->global_data.pipe_status[p_data->cmd_count]);
				}
			}
			else
			{
				if (cmd_tree->kind == T_COMMAND)
				{
					p_data->cmd = cmd_tree->argv;
					shell_execute(p_data);
				}
			}
			++p_data->cmd_count;
			p_data->is_fileio_success = 1;
			p_data->fd_out_new = 0;
			p_data->fd_in_new = 0;
		}
		tree_traverse_exe_cmd(p_data, cmd_tree->left);
		tree_traverse_exe_cmd(p_data, cmd_tree->right);
	}
}

void	shell_execute_tree(t_shell_data *p_data)
{
	pid_t				pid;
	t_shell_tree_node	*cur;

	if (!p_data)
		return ;
#if DEBUG_TREE == 1
	print_heredoc(p_data);
	print_tree(p_data);
#endif
	p_data->fd_out_old = dup(STDOUT_FILENO);
	p_data->fd_in_old = dup(STDIN_FILENO);
	//p_data->fd_out_new = dup(STDOUT_FILENO);
	//p_data->fd_in_new = dup(STDIN_FILENO);
	p_data->pipe_index = 0;
	p_data->pipe_fd = malloc(p_data->pipe_count * sizeof(int[2]));
	p_data->global_data.pipe_status = malloc((p_data->pipe_count + 1) * sizeof(int));
	p_data->global_data.pipe_pid = malloc((p_data->pipe_count + 1) * sizeof(pid_t));
	p_data->is_piped = 0;
	p_data->pipe_num = p_data->pipe_count;
	p_data->is_fileio_success = 1;

	cur = &p_data->tree;
	tree_traverse_set_pipe(p_data, cur);
	cur = &p_data->tree;
	p_data->cmd_count = 0;
	p_data->pipe_num = p_data->pipe_count;
	p_data->fd_out_new = 0;
	p_data->fd_in_new = 0;
	tree_traverse_exe_cmd(p_data, cur);
	dup2(p_data->fd_out_old, STDOUT_FILENO);
	dup2(p_data->fd_in_old, STDIN_FILENO);
	for (int i = 0; i < p_data->pipe_count; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			close(p_data->pipe_fd[i][j]);
		}
	}
	while (1)
	{
		pid = wait(&p_data->process_exit_status);
		for (int i = 0; i < p_data->pipe_count + 1; i++)
			if (pid == p_data->global_data.pipe_pid[i])
			{
				p_data->global_data.pipe_status[i] = (128 + (p_data->process_exit_status & 0x7f)) * ((p_data->process_exit_status & 0x7f) != 0) + (p_data->process_exit_status >> 8);
			}
			if (pid == -1)
				break ;
	}
	fprintf(stderr, "exit:");
	for (int i = 0; i < p_data->pipe_count + 1; i++)
		fprintf(stderr, "%d ", p_data->global_data.pipe_status[i]);
	fprintf(stderr, "\n");
	if (p_data->line)
		free(p_data->line);
	shell_parse_free(p_data);
	shell_parse_init(p_data);
	ft_set_status(p_data, S_LINE_READ);
	dup2(p_data->fd_out_old, STDOUT_FILENO);
	dup2(p_data->fd_in_old, STDIN_FILENO);
	close(p_data->fd_out_old);
	close(p_data->fd_in_old);
	p_data->exit_code = p_data->global_data.pipe_status[p_data->pipe_count];
	p_data->pipe_count = 0;
	free(p_data->pipe_fd);
	free(p_data->global_data.pipe_status);
	free(p_data->global_data.pipe_pid);
	set_tc_attr(p_data);
	return ;
}
