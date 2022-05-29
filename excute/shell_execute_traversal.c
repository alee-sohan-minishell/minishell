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

void	set_fd(t_shell_data *p_data, const char *filename, int type)
{
	if (type == REDI_IN)
		redirection_in(p_data, filename);
	else if (type == REDI_OUT)
		redirection_out(p_data, filename);
	else if (type == APPEND)
		redirection_append(p_data, filename);
}

void	dfs(t_graph *graph, int	vertex_id, t_shell_data *p_data)
{
	t_node	*close_node;
	t_node	*cur_node;
	//pid_t	pid;
	//int		status;

	cur_node = graph->edge[vertex_id];
	if (cur_node->visited == 1)
		return ;
	cur_node->visited = 1;
	p_data->cmd = cur_node->cmd;
	close_node = graph->edge[vertex_id]->next;
	if (cur_node->type)
	{	
		set_fd(p_data, close_node->cmd[0], cur_node->type);
		graph->edge[close_node->vertex_id]->visited = 1;
	}
	shell_excute(p_data);
	while (close_node)
	{
		//if (close_node->type == '|')
		//{	
			//pid = fork();
			//if (pid == 0)
			//	shell_excute(p_data);
			//wait(&status);
		//}
		//else
			//shell_excute(p_data);
		dfs(graph, close_node->vertex_id, p_data);
		close_node = close_node->next;
	}
}

void	shell_execute_traversal(t_shell_data *p_data)
{
	int		index;

	index = 0;
	if (!p_data)
		return ;
	p_data->fd_out_old = dup(STDOUT_FILENO);
	p_data->fd_in_old = dup(STDIN_FILENO);
	dfs(p_data->cmd_graph, 0, p_data);
	destroy_graph(p_data->cmd_graph);
	if (p_data->line)
		free(p_data->line);
	ft_set_status(p_data, S_LINE_READ);
	dup2(p_data->fd_out_old, STDOUT_FILENO);
	dup2(p_data->fd_in_old, STDIN_FILENO);
	close(p_data->fd_out_old);
	close(p_data->fd_in_old);
	return ;
}
