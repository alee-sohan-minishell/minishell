#include "../shell/shell.h"
#include "../libft/libft.h"
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

void	set_pipe(t_shell_data *p_data)
{

	--p_data->pipe_num;
	if (pipe(p_data->pipe_fd[p_data->pipe_num]) == -1)
		printf("pipe error\n");
	//p_data->pipe_pid[0] = fork();
	//p_data->pipe_pid[1] = fork();
	//if (p_data->pipe_pid[0] == 0)
	/*p_data->fd_out_new = p_data->pipe_fd[1];
	{
		dup2(p_data->pipe_fd[1], p_data->fd_out_new);
		close(p_data->pipe_fd[0]);
	}*/
	//printf("fd[0]:%d fd[1]:%d\n", p_data->pipe_fd[p_data->pipe_index][0], p_data->pipe_fd[p_data->pipe_index][1]);
	//++p_data->pipe_index;
	//p_data->is_piped = 1;
	//if (p_data->pipe_pid[1] == 0)
	//{
	//	dup2(p_data->pipe_fd[0], p_data->fd_in_new);
	//	close(p_data->pipe_fd[1]);
	//}
}

//void	set_fd(t_shell_data *p_data, const char *filename, int type)
int	set_fd(t_shell_data *p_data, t_shell_tree_node *cmd_tree)
{
	if (cmd_tree->kind == T_REDIRECT_IN)
	{
		if (redirection_in(p_data, cmd_tree->filepath) == -1)
			return (-1);
	}
	else if (cmd_tree->kind == T_REDIRECT_OUT)
	{
		if (redirection_out(p_data, cmd_tree->filepath) == -1)
			return (-1);
	}
	else if (cmd_tree->kind == T_REDIRECT_APPEND)
	{
		if (redirection_append(p_data, cmd_tree->filepath) == -1)
			return (-1);
	}
	else if (cmd_tree->kind == T_PIPE)
		set_pipe(p_data);
	return (0);
}

/*void	make_command_array(t_shell_data *p_data, t_shell_tree_node *cmd_tree)
{
	char	*tmp;

	if (cmd_tree->left)
		;
}*/

void	tree_traverse_set_io(t_shell_data *p_data, t_shell_tree_node *cmd_tree)
{
	if (cmd_tree)
	{
		//do something here
		if (set_fd(p_data, cmd_tree) == -1)
			return ;
		tree_traverse_set_io(p_data, cmd_tree->left);
		tree_traverse_set_io(p_data, cmd_tree->right);
	}
}

void	tree_traverse_exe_cmd(t_shell_data *p_data, t_shell_tree_node *cmd_tree)
{
	if (cmd_tree)
	{
		if (cmd_tree->kind == T_COMMAND)
		{
			p_data->cmd = cmd_tree->argv;
			printf("excute %s\n", p_data->cmd[0]);
			shell_excute(p_data);
			--p_data->cmd_count;
		}
		tree_traverse_exe_cmd(p_data, cmd_tree->left);
		tree_traverse_exe_cmd(p_data, cmd_tree->right);
	}
}

void	shell_execute_tree(t_shell_data *p_data)
{
	int		all_done = 0;
	pid_t	pid;
	t_shell_tree_node *cur;

	if (!p_data)
		return ;
	p_data->fd_out_old = dup(STDOUT_FILENO);
	p_data->fd_in_old = dup(STDIN_FILENO);
	p_data->fd_out_new = dup(STDOUT_FILENO);
	p_data->fd_in_new = dup(STDIN_FILENO);
	p_data->pipe_index = 0;
	p_data->pipe_fd = malloc(p_data->pipe_count * sizeof(int[2]));
	p_data->global_data.pipe_status = malloc(p_data->pipe_count + 1 * sizeof(int));
	p_data->global_data.pipe_pid = malloc(p_data->pipe_count + 1 * sizeof(pid_t));
	all_done = 0;
	p_data->global_data.index = 0;
	p_data->pipe_num = p_data->pipe_count;
	p_data->cmd_count = p_data->pipe_count;

	cur = p_data->cmd_tree;
	printf("root? %d\n", cur->idx);
	tree_traverse_set_io(p_data, cur);
	cur = p_data->cmd_tree;
	printf("root? %d\n", cur->idx);
	tree_traverse_exe_cmd(p_data, cur);
	//printf("i'm waiting for process id %d and %d\n", p_data->global_data.pipe_pid[0], p_data->global_data.pipe_pid[1]);
	/*if (!p_data->is_piped)
	{
		wait(&p_data->process_exit_status);
		p_data->global_data.pipe_status[1] = (128 + (p_data->process_exit_status & 0x7f)) * ((p_data->process_exit_status & 0x7f) != 0) + (p_data->process_exit_status >> 8);
	}
	else*/
		for (int i = 0; i < p_data->pipe_count + 1; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				close(p_data->pipe_fd[i][j]);
			}
		}
		//close(p_data->pipe_fd[1]);
		//close(p_data->pipe_fd[0]);
		while (all_done < p_data->pipe_count + 1)
		{
			pid = wait(&p_data->process_exit_status);
			printf("pid:%d\n", pid);
			for (int i = 0; i < p_data->pipe_count + 1; i++)
				if (pid == p_data->global_data.pipe_pid[i])
			{	
				p_data->global_data.pipe_status[p_data->pipe_count - i] = (128 + (p_data->process_exit_status & 0x7f)) * ((p_data->process_exit_status & 0x7f) != 0) + (p_data->process_exit_status >> 8);
				++all_done;
			}
		}
		//while ((pid = wait(NULL)) != -1);
	if (p_data->line)
		free(p_data->line);
	ft_set_status(p_data, S_LINE_READ);
	dup2(p_data->fd_out_old, STDOUT_FILENO);
	dup2(p_data->fd_in_old, STDIN_FILENO);
	close(p_data->fd_out_old);
	close(p_data->fd_in_old);
	return ;
}
