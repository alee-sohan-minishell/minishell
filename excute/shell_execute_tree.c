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

	if (pipe(p_data->pipe_fd) == -1)
		printf("pipe error\n");
	//p_data->pipe_pid[0] = fork();
	//p_data->pipe_pid[1] = fork();
	//if (p_data->pipe_pid[0] == 0)
	p_data->fd_in_new = p_data->pipe_fd[0];
	{
		dup2(p_data->pipe_fd[0], p_data->fd_in_new);
		close(p_data->pipe_fd[1]);
	}
	p_data->is_piped = 1;
	//if (p_data->pipe_pid[1] == 0)
	//{
	//	dup2(p_data->pipe_fd[0], p_data->fd_in_new);
	//	close(p_data->pipe_fd[1]);
	//}
}

//void	set_fd(t_shell_data *p_data, const char *filename, int type)
void	set_fd(t_shell_data *p_data, t_shell_tree_node *cmd_tree)
{
	if (cmd_tree->kind == T_REDIRECT_IN)
		redirection_in(p_data, cmd_tree->filepath);
	else if (cmd_tree->kind == T_REDIRECT_OUT)
		redirection_out(p_data, cmd_tree->filepath);
	else if (cmd_tree->kind == T_REDIRECT_APPEND)
		redirection_append(p_data, cmd_tree->filepath);
	else if (cmd_tree->kind == T_PIPE)
		set_pipe(p_data);
}

/*void	make_command_array(t_shell_data *p_data, t_shell_tree_node *cmd_tree)
{
	char	*tmp;

	if (cmd_tree->left)
		;
}*/

void	tree_traverse(t_shell_data *p_data, t_shell_tree_node *cmd_tree)
{
	if (cmd_tree)
	{
		//do something here
		set_fd(p_data, cmd_tree);
		if (cmd_tree->kind == T_COMMAND)
		{
			p_data->cmd = cmd_tree->argv;
			shell_excute(p_data);
		}
		tree_traverse(p_data, cmd_tree->left);
		tree_traverse(p_data, cmd_tree->right);
	}
}

void	shell_execute_tree(t_shell_data *p_data)
{
	if (!p_data)
		return ;
	p_data->fd_out_old = dup(STDOUT_FILENO);
	p_data->fd_in_old = dup(STDIN_FILENO);
	p_data->fd_out_new = dup(STDOUT_FILENO);
	p_data->fd_in_new = dup(STDIN_FILENO);
	tree_traverse(p_data, p_data->cmd_tree);
	wait(&p_data->p_status);
	p_data->term_status = (128 + (p_data->p_status & 0x7f)) * ((p_data->p_status & 0x7f) != 0) + (p_data->p_status >> 8);

	if (p_data->line)
		free(p_data->line);
	ft_set_status(p_data, S_LINE_READ);
	dup2(p_data->fd_out_old, STDOUT_FILENO);
	dup2(p_data->fd_in_old, STDIN_FILENO);
	close(p_data->fd_out_old);
	close(p_data->fd_in_old);
	return ;
}
