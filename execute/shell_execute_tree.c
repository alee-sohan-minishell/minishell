/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_execute_tree.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 00:15:36 by sohan             #+#    #+#             */
/*   Updated: 2022/06/29 19:53:48 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_execute.h"
#include "../utils/state_machine_utils_01.h"
#include "../init/shell_utils_01.h"
#include "../init/shell_parse_init.h"
#include "../parse/shell_parse.h"
#include "../utils/error_msg_utils_02.h"
#include <stdlib.h>
#include <unistd.h>
#include "../print.h"

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

void	restore_stdio(t_shell_data *p_data)
{
	dup2(p_data->cp_stdout, STDOUT_FILENO);
	dup2(p_data->cp_stdin, STDIN_FILENO);
}

void	shell_execute_tree_init(t_shell_data *p_data)
{
	p_data->pipe_status = malloc((p_data->pipe_count + 1) * sizeof(int));
	p_data->pipe_pid = malloc((p_data->pipe_count + 1) * sizeof(pid_t));
	if (!p_data->pipe_status || !p_data->pipe_pid)
		ft_self_perror_param_exit(NULL, "Init pipe data", \
										"Error while malloc", 1);
	p_data->cmd_count = 0;
	p_data->fileio_errno = 0;
	p_data->fd_new[OUT] = 0;
	p_data->fd_new[IN] = 0;
	p_data->is_piped = p_data->pipe_count;
}

void	shell_execute_tree(t_shell_data *p_data)
{
	t_shell_tree_node	*cur;

	if (!p_data)
		return ;
	if (DEBUG_TREE == 1)
		print_tree(p_data);
	shell_execute_tree_init(p_data);
	cur = &p_data->tree;
	tree_traverse_execute(p_data, cur);
	restore_stdio(p_data);
	wait_children(p_data);
	g.exit_code = p_data->pipe_status[p_data->pipe_count];
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
}
