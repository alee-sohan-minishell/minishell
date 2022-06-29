/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_execute_tree.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 00:15:36 by alee              #+#    #+#             */
/*   Updated: 2022/06/29 18:25:54 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_execute.h"
#include "../utils/state_machine_utils_01.h"
#include "../init/shell_utils_01.h"
#include "../init/shell_parse_init.h"
#include "../parse/shell_parse.h"
#include "../utils/error_msg_utils_01.h"
#include <stdlib.h>
#include <unistd.h>

void	tree_traverse_get_pipe_fd(t_shell_data *p_data,
												t_shell_tree_node *cmd_tree)
{
	if (cmd_tree)
	{
		if (cmd_tree->kind == T_PIPE)
		{
			--p_data->pipe_num;
			if (pipe(p_data->pipe_fd[p_data->pipe_num]) == -1)
				ft_perror_exit("pipe error", 1);
			p_data->is_piped = 1;
		}
		tree_traverse_get_pipe_fd(p_data, cmd_tree->left);
		tree_traverse_get_pipe_fd(p_data, cmd_tree->right);
	}
}

void	wait_children(t_shell_data *p_data)
{
	pid_t	pid;
	int		index;
	int		status;

	index = 0;
	while (1)
	{
		pid = wait(&status);
		while (index < p_data->pipe_count + 1)
		{
			if (pid == p_data->pipe_pid[index])
				p_data->pipe_status[index] = \
					WIFSIGNALED(status) * (128 + WTERMSIG(status)) \
														+ WEXITSTATUS(status);
			++index;
		}
		if (pid == -1)
			break ;
		index = 0;
	}
}

void	shell_execute_tree(t_shell_data *p_data)
{
	t_shell_tree_node	*cur;

	if (!p_data)
		return ;
	shell_execute_tree_init(p_data);
	cur = &p_data->tree;
	tree_traverse_get_pipe_fd(p_data, cur);
	cur = &p_data->tree;
	tree_traverse_execute(p_data, cur);
	restore_stdio(p_data->fd_std);
	close_pipe_fd(p_data);
	wait_children(p_data);
	g_exit_code = p_data->pipe_status[p_data->pipe_count];
	shell_parse_free(p_data);
	shell_parse_init(p_data);
	p_data->pipe_count = 0;
	free(p_data->pipe_fd);
	free(p_data->pipe_status);
	free(p_data->pipe_pid);
	if (p_data->line)
		free(p_data->line);
	set_tc_attr(p_data);
	ft_set_status(p_data, S_LINE_READ);
	return ;
}
