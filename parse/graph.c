/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:34:33 by sohan             #+#    #+#             */
/*   Updated: 2022/03/11 15:34:35 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_parse.h"
#include "../libft/libft.h"

t_node	**create_list(int max_vertex_count)
{
	t_node	**tmp_list;
	int		index;

	index = 0;
	tmp_list = ft_calloc(max_vertex_count, sizeof(t_node *));
	if (!tmp_list)
		return (NULL);
	while (index < max_vertex_count)
	{
		tmp_list[index] = ft_calloc(1, sizeof(t_node));
		if (!tmp_list[index])
		{
			while (--index > -1)
				free(tmp_list[index]);
			free(tmp_list);
			return (NULL);
		}
		tmp_list[index]->vertex_id = index;
		index++;
	}
	return (tmp_list);
}

t_graph	*create_graph(int max_vertex_count)
{
	t_graph	*tmp;
	t_node	**tmp_list;
	int		*tmp_vertex;

	tmp = ft_calloc(1, sizeof(t_graph));
	if (!tmp || !max_vertex_count)
		return (NULL);
	tmp->max_vertex_count = max_vertex_count;
	tmp->current_vertex_count = 0;
	tmp_list = create_list(max_vertex_count);
	if (!tmp_list)
		return (NULL);
	tmp->edge = tmp_list;
	tmp_vertex = ft_calloc(max_vertex_count, sizeof(int));
	if (!tmp_vertex)
		return (NULL);
	tmp->vertex = tmp_vertex;
	return (tmp);
}

int is_vertex_valid(t_graph* graph, int vertex_id)
{
	if (vertex_id >= graph->max_vertex_count)
		return (0);
	if (graph->vertex[vertex_id])
        return (1);
    return (0);
}

int	add_vertex(t_graph *graph, int vertex_id)
{
	//t_node	*ptr;

	if (vertex_id < 0 || vertex_id >= graph->max_vertex_count)
		return (-1);
	if (!graph->vertex[vertex_id])
		graph->current_vertex_count++;
	graph->vertex[vertex_id] = 1;
	//ptr = graph->edge[vertex_id];
	//ptr->cmd = cmd;
	return (0);
}

int	add_edge(t_graph *graph, int from_vertex_id, \
									int to_vertex_id, int type)
{
	t_node	*tmp;
	t_node	*ptr;

	if (!is_vertex_valid(graph, to_vertex_id))
		return (-1);
	tmp = ft_calloc(1, sizeof(t_node));
	if (!tmp)
		return (-1);
	tmp->vertex_id = to_vertex_id;
	ptr = graph->edge[from_vertex_id];
	ptr->type = type;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = tmp;
	graph->current_edge_count++;
	return (0);
}

void destroy_graph(t_graph* graph)
{
	int	j = 0;

	if (!graph->current_vertex_count)
		return ;
	/* edge free */
	for (int i = 0; i < graph->max_vertex_count; i++)
	{
		j = 0;
		while (graph->edge[i]->cmd[j])
		{
			free(graph->edge[i]->cmd[j]);
			++j;
		}
		free(graph->edge[i]->cmd);
	}
	for (int i = 0; i < graph->max_vertex_count; i++)
	{	
		while (graph->edge[i])
		{
		    t_node  	*tmp = graph->edge[i];
            graph->edge[i] = graph->edge[i]->next;
			free(tmp);
		}
	}
	free(graph->edge);
	graph->edge = NULL;
	free(graph->vertex);
    graph->vertex = NULL;
	free(graph);
	//graph->max_vertex_count = graph->current_vertex_count = graph->current_edge_count = 0;
	//printf("Graph deleted\n");
}

void display_graph(t_graph* pGraph)
{
	if (!pGraph->current_vertex_count)
	{
        printf("Graph is Empty.\n");
        return ;
    }
	printf("\n< Graph > - \n");
	/* edge print */
	for (int i = 0; i < pGraph->max_vertex_count; i++)
    {
        t_node *tmp = pGraph->edge[i];
		if (is_vertex_valid(pGraph, tmp->vertex_id))
			printf("\e[32m(O)");
		else	printf("\e[31m(X)");
        while (tmp)
        {
            //printf("%d[%s]\e[0m", tmp->vertex_id, tmp->cmd);
            tmp = tmp->next;
			if (tmp) printf(" -> ");
        }
        printf("\n");
    }
	/* vertex print */
	printf("Vertex: ");
	for (int i = 0; i < pGraph->max_vertex_count; i++)
	{
		if (pGraph->vertex[i])
			printf("\e[32m");
		else	printf("\e[31m");
		printf("%d\e[0m\t", pGraph->vertex[i]);
	}
	printf("\n\n");
}
