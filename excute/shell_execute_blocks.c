#include "../shell/shell.h"
#include "../libft/libft.h"
#include "../init/shell_utils_01.h"
#include "../utils/state_machine_utils_01.h"
#include "../signal/signal.h"
#include "shell_excute.h"

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
	close_node = graph->edge[vertex_id]->next;
	p_data->cmd = ft_split(cur_node->cmd, ' ');
	printf("%d[%s]\n", cur_node->vertex_id, cur_node->cmd);
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

void	free_graph_array(t_shell_data *p_data)
{
	int	index;

	index = 0;
	while (p_data->cmd_graph[index])
	{
		destroy_graph(p_data->cmd_graph[index]);
		++index;
	}
	//free(p_data->cmd_graph[index]);
	free(p_data->cmd_graph);
}

void	shell_execute_blocks(t_shell_data *p_data)
{
	int		index;
	//int		index2;
	//pid_t	pid;
	//int		status;

	index = 0;
	//index2 = 0;
	if (!p_data)
		return ;
	while (p_data->cmd_graph[index])
	{
		dfs(p_data->cmd_graph[index], 0, p_data);
		//p_data->cmd = ft_split(p_data->cmd_graph[index]->edge[index]->cmd, ' ');
		//printf("%s\n", p_data->cmd[0]);
		//pid = fork();
		//if (pid > 0)
		/*if (pid == 0)
		{
			shell_excute(p_data);
			exit(p_data->term_status);
		}
			wait(&status);
		printf("%d\n", status >> 8);*/
		++index;
	}
	free_graph_array(p_data);
	if (p_data->line)
		free(p_data->line);
	ft_set_status(p_data, S_LINE_READ);
	return ;
}
