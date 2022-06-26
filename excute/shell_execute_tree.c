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
#define WRITE 1
#define READ 0

void	set_pipe_fd(t_shell_data *p_data)
{
	--p_data->pipe_num;
	for (int i = 0; i < p_data->pipe_num - 1; i++)
		{
			close(p_data->pipe_fd[i][READ]);
			close(p_data->pipe_fd[i][WRITE]);
		}
		if (p_data->pipe_num > 0)
		{
			close(p_data->pipe_fd[p_data->pipe_num - 1][WRITE]);
			//p_data->fd_in_new = p_data->pipe_fd[p_data->pipe_num - 1][READ];
			dup2(p_data->pipe_fd[p_data->pipe_num - 1][READ], STDIN_FILENO);
			close(p_data->pipe_fd[p_data->pipe_num - 1][READ]);
		}
		if (p_data->pipe_num < p_data->pipe_count)
		{
			close(p_data->pipe_fd[p_data->pipe_num][READ]);
			//p_data->fd_out_new = p_data->pipe_fd[p_data->pipe_num][READ];
			dup2(p_data->pipe_fd[p_data->pipe_num][WRITE], STDOUT_FILENO);
			close(p_data->pipe_fd[p_data->pipe_num][WRITE]);
		}
		for (int i = p_data->pipe_num + 1; i < p_data->pipe_count; i++)
		{
			close(p_data->pipe_fd[i][READ]);
			close(p_data->pipe_fd[i][WRITE]);
		}
}

void	set_pipe(t_shell_data *p_data)
{

	--p_data->pipe_num;
	if (pipe(p_data->pipe_fd[p_data->pipe_num]) == -1)
		fprintf(stderr,"pipe error\n");
		
	
	//++p_data->pipe_index;
	//p_data->pipe_pid[0] = fork();
	//p_data->pipe_pid[1] = fork();
	//if (p_data->pipe_pid[0] == 0)
	/*p_data->fd_out_new = p_data->pipe_fd[1];
	{
		dup2(p_data->pipe_fd[1], p_data->fd_out_new);
		close(p_data->pipe_fd[0]);
	}*/
	//fprintf(stderr,"fd[0]:%d fd[1]:%d\n", p_data->pipe_fd[p_data->pipe_index][0], p_data->pipe_fd[p_data->pipe_index][1]);
	//++p_data->pipe_index;
	p_data->is_piped = 1;
	//if (p_data->pipe_pid[1] == 0)
	//{
	//	dup2(p_data->pipe_fd[0], p_data->fd_in_new);
	//	close(p_data->pipe_fd[1]);
	//}
}

//void	set_fd(t_shell_data *p_data, const char *filename, int type)
//
//debug
#include <stdio.h>
#include "../tree_heredoc/shell_heredoc.h"

int	set_fd(t_shell_data *p_data, t_shell_tree_node *cmd_tree)
{
	if (cmd_tree->kind == T_REDIRECT_HEREDOC)
	{
		//TODO : heredoc의 eof 문자열이 파싱 구조에 보이지 않음
		// p_data->heredoc_list.head.delimiter와 같이 heredoc리스트의 delimiter를 넣어주어야 한다.
		if (heredoc(p_data, cmd_tree->filepath) == -1)
			return (-1);
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
			return (-1);
	}
	else if (cmd_tree->kind == T_REDIRECT_APPEND)
	{
		if (redirection_append(p_data, cmd_tree->filepath) == -1)
			return (-1);
	}
	return (0);
}

/*void	make_command_array(t_shell_data *p_data, t_shell_tree_node *cmd_tree)
{
	char	*tmp;

	if (cmd_tree->left)
		;
}*/

void	tree_traverse_set_pipe(t_shell_data *p_data, t_shell_tree_node *cmd_tree)
{
	if (cmd_tree)
	{
		//do something here
		if (cmd_tree->kind == T_PIPE)
			set_pipe(p_data);
		tree_traverse_set_pipe(p_data, cmd_tree->left);
		tree_traverse_set_pipe(p_data, cmd_tree->right);
	}
}

void	tree_traverse_exe_cmd(t_shell_data *p_data, t_shell_tree_node *cmd_tree)
{
	if (cmd_tree)
	{
		//if (set_fd(p_data, cmd_tree) == -1)
		//	p_data->is_fileio_success = 0;
		set_fd(p_data, cmd_tree);
		//else
		//	p_data->is_fileio_success = 1;
		if (cmd_tree->kind == T_PIPE)
			set_pipe_fd(p_data);
		if (cmd_tree->kind == T_COMMAND)
		{
			p_data->cmd = cmd_tree->argv;
			shell_excute(p_data);
			++p_data->cmd_count;
		}
		tree_traverse_exe_cmd(p_data, cmd_tree->left);
		// TODO && ||
		//dup2(p_data->fd_out_old, STDOUT_FILENO);
		if (cmd_tree->kind == T_PIPE)
		{
			++p_data->pipe_num;
			set_pipe_fd(p_data);
		}
		tree_traverse_exe_cmd(p_data, cmd_tree->right);
	}
}

void	shell_execute_tree(t_shell_data *p_data)
{
	pid_t				pid;
	t_shell_tree_node	*cur;

	if (!p_data)
		return ;
	p_data->fd_out_old = dup(STDOUT_FILENO);
	p_data->fd_in_old = dup(STDIN_FILENO);
	p_data->fd_out_new = dup(STDOUT_FILENO);
	p_data->fd_in_new = dup(STDIN_FILENO);
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
	tree_traverse_exe_cmd(p_data, cur);
	//fprintf(stderr,"i'm waiting for process id %d and %d\n", p_data->global_data.pipe_pid[0], p_data->global_data.pipe_pid[1]);
	/*if (!p_data->is_piped)
	{
		wait(&p_data->process_exit_status);
		p_data->global_data.pipe_status[1] = (128 + (p_data->process_exit_status & 0x7f)) * ((p_data->process_exit_status & 0x7f) != 0) + (p_data->process_exit_status >> 8);
	}
	else*/
		if (p_data->is_piped)
		{
			for (int i = 0; i < p_data->pipe_count; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					close(p_data->pipe_fd[i][j]);
				}
			}
		}
			close(p_data->fd_in_new);
			close(p_data->fd_out_new);
		//close(p_data->pipe_fd[1]);
		//close(p_data->pipe_fd[0]);
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
	fprintf(stderr,"exit:");
	for (int i = 0; i < p_data->pipe_count + 1; i++)
		fprintf(stderr,"%d ", p_data->global_data.pipe_status[i]);
	fprintf(stderr,"\n");
		//while ((pid = wait(NULL)) != -1);
	if (p_data->line)
		free(p_data->line);
	shell_parse_free(p_data);
	shell_parse_init(p_data);
	ft_set_status(p_data, S_LINE_READ);
	dup2(p_data->fd_out_old, STDOUT_FILENO);
	dup2(p_data->fd_in_old, STDIN_FILENO);
	close(p_data->fd_out_old);
	close(p_data->fd_in_old);
	p_data->exit_code = p_data->global_data.pipe_status[p_data->pipe_count]; // free 하기전에 마지막 파이프 exit_code 가지고 있어야 파싱에서 $? 치환할 때 사용 가능
	p_data->pipe_count = 0;
	free(p_data->pipe_fd);
	free(p_data->global_data.pipe_status);
	free(p_data->global_data.pipe_pid);
	set_tc_attr(p_data);
	return ;
}
