/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_traverse_execute.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:14:04 by sohan             #+#    #+#             */
/*   Updated: 2022/06/29 18:25:56 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_execute.h"
#include "../utils/error_msg_utils_01.h"
#include "../env/env_list_interface_01.h"
#include "../redirection/redirection.h"
#include "../heredoc/heredoc.h"
#include "../init/shell_utils_01.h"
#include "../signal/signal.h"
#include "../libft/libft.h"

void	set_redirection_fd(t_shell_data *p_data, t_shell_tree_node *cmd_tree)
{
	if (cmd_tree->kind == T_REDIRECT_HEREDOC)
	{
		if (heredoc(p_data, cmd_tree->filepath) == -1)
			p_data->fileio_errno = 1;
	}
	else if (cmd_tree->kind == T_REDIRECT_IN)
	{
		if (redirection_in(p_data, cmd_tree->filepath) == -1)
			p_data->fileio_errno = 1;
	}
	else if (cmd_tree->kind == T_REDIRECT_OUT)
	{
		if (redirection_out(p_data, cmd_tree->filepath) == -1)
			p_data->fileio_errno = 1;
	}
	else if (cmd_tree->kind == T_REDIRECT_APPEND)
	{
		if (redirection_append(p_data, cmd_tree->filepath) == -1)
			p_data->fileio_errno = 1;
	}
}

void	execute_command(t_shell_data *p_data, t_shell_tree_node *cmd_tree)
{
	if (cmd_tree->kind == T_COMMAND)
	{
		p_data->cmd = cmd_tree->argv;
		shell_execute_command_name(p_data);
	}
}

void	fork_execute_command(t_shell_data *p_data, t_shell_tree_node *cmd_tree)
{
	pid_t	pid;

	pid = fork();
	if (pid > 0)
	{
		p_data->pipe_pid[p_data->cmd_count] = pid;
		set_io_parent(p_data);
	}
	else if (pid == 0)
	{
		set_io_child(p_data);
		execute_command(p_data, cmd_tree);
		exit(p_data->pipe_status[p_data->cmd_count]);
	}
	else
		ft_perror_exit("fork failed", 1);
}

void	set_background_signal(t_shell_data *p_data, t_shell_tree_node *cmd_tree)
{
	t_env_node	*cur_node;

	shell_command_is_foreground_process();
	if (cmd_tree->argv
		&& ft_strnstr(cmd_tree->argv[0], "minishell", \
												ft_strlen(cmd_tree->argv[0])))
		minishell_is_foreground_process();
	else if (cmd_tree->argv \
			&& (ft_strnstr(cmd_tree->argv[0], "./", \
												ft_strlen(cmd_tree->argv[0]))
			|| env_node_search(&p_data->env_list, "PATH", &cur_node) == 0))
		executable_file_is_foreground_process();
}

void	tree_traverse_execute(t_shell_data *p_data, t_shell_tree_node *cmd_tree)
{
	if (cmd_tree)
	{
		if (p_data->fileio_errno == 0)
			set_redirection_fd(p_data, cmd_tree);
		if (!cmd_tree->left && !cmd_tree->right)
		{
			set_background_signal(p_data, cmd_tree);
			set_tc_attr_to_default(p_data);
			if (p_data->is_piped)
				fork_execute_command(p_data, cmd_tree);
			else
				execute_command(p_data, cmd_tree);
			++p_data->cmd_count;
			p_data->fileio_errno = 0;
			p_data->fd_new[OUT] = 0;
			p_data->fd_new[IN] = 0;
		}
		tree_traverse_execute(p_data, cmd_tree->left);
		tree_traverse_execute(p_data, cmd_tree->right);
	}
}
