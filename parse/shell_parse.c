/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:08:02 by alee              #+#    #+#             */
/*   Updated: 2022/05/26 13:16:45 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "../utils/state_machine_utils_01.h"
#include "../libft/libft.h"

/****************temp implementation**********/
#include "../env/env_list_interface_01.h"

int	is_seperator(char *charset, char c)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

int		cmd_count(const char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (*str)
	{
		while (str[i] && !is_seperator("|<>", str[i]))
			++i;
		str += i;
		if (is_seperator("|<>", *str))
			++str;
		if (is_seperator("|<>", *str))
			++str;
		i = 0;
		++count;
	}
	return (count);
}

t_graph	*cmd_split(const char *str, char *sep, int size)
{
	t_graph	*graph;
	char	*cmd;
	char	**tmp;
	int		i;
	int		count;
	int		type;

	i = 0;
	count = 0;
	type = 0;
	graph = create_graph(size);
	while (i < size)
	{
		add_vertex(graph, i);
		++i;
	}
	i = 0;
	while (*str)
	{
		while (str[i] && !is_seperator(sep, str[i]))
			++i;
		cmd = ft_strndup(str, i);
		tmp = ft_split(cmd, ' ');
		free(cmd);
		graph->edge[count]->cmd = tmp;
		str += i;
		if (is_seperator(sep, *str))
		{
			if (*str == '|')
				type = PIPE;
			else if (*str == '<')
				type = REDI_IN;
			else if (*str == '>')
				type = REDI_OUT;
			++str;
		}
				//if (is_seperator(sep, *str))
		if (*str == '>')
		{
			type = APPEND;
			++str;
		}
		add_edge(graph, count, count + 1, type);
		if (count)
			graph->edge[count - 1]->next->cmd = tmp;
		i = 0;
		++count;
	}
	return (graph);
}
/****************** to here********************/

void	shell_parse(t_shell_data *p_data)
{
	if (!p_data)
		return ;
	p_data->cmd_count = cmd_count(p_data->line);
	if (!p_data->cmd_count)
	{
		ft_set_status(p_data, S_LINE_READ);
		free(p_data->line);
		return ;
	}
	p_data->cmd_graph = cmd_split(p_data->line, "|<>", p_data->cmd_count);
	//printf("count:%d\n", p_data->cmd_count);
	//display_graph(p_data->cmd_graph);
	/*p_data->cmd = ft_split(p_data->line, ' ');
	if (!p_data->cmd)
	{
		ft_set_status(p_data, S_ERROR);
		return ;
	}*/
	ft_set_status(p_data, S_CMD);
	return ;
}
