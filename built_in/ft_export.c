/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 02:51:07 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 05:49:26 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "../utils/command_utils_01.h"
#include "../libft/libft.h"
#include "ft_export.h"
#include <unistd.h>
#include "../utils/error_msg_utils_01.h"

int	ft_export(char **cmd, t_env_list *p_list)
{
	if (!cmd || !(*cmd) || !p_list)
		return (1);
	if (get_cmd_count(cmd) > 1)
	{
		printf("A");
	}
	else
	{
		print_export(p_list);
	}

	return (0);
}

void	print_export(t_env_list *p_list)
{
	char	**buf;
	int		str_count;

	if (malloc_export_buffer(&buf, p_list, &str_count) == 0)
		ft_msg_exit("Export malloc Failed \n", 1, STDERR_FILENO);
	copy_export_buffer(&buf, p_list);
	//sort_export_buffer(&buf, str_count);
	//print_export_buffer(&buf);
	//free_export_buffer(&buf, str_count);
	return ;
}


int		malloc_export_buffer(char ***buf, t_env_list *p_list, int *buf_count)
{
	t_env_node	*cur_node;
	int			buf_len;
	int			idx;

	if (!buf)
		return (0);
	*buf = (char **)malloc(sizeof(char *) * p_list->node_count);
	if (!(*buf))
		return (0);
	cur_node = p_list->dummy_head.next;
	buf_len = 0;
	idx = 0;
	while (cur_node != &p_list->dummy_tail)
	{
		buf_len = ft_strlen(cur_node->key);
		if (cur_node->value)
			buf_len += ft_strlen("=") + ft_strlen(cur_node->value);
		(*buf)[idx] = (char *)malloc(buf_len + 1);
		if (!((*buf)[idx]))
			return (free_export_buffer(buf, idx));
		cur_node = cur_node->next;
		idx++;
	}
	*buf_count = idx;
	return (1);
}

int		free_export_buffer(char ***buf, int idx)
{
	int	cur_idx;

	if (!buf)
		return (-1);
	cur_idx = 0;
	while (cur_idx < idx)
	{
		free((*buf)[cur_idx]);
		cur_idx++;
	}
	free(*buf);
	return (0);
}

void	copy_export_buffer(char ***buf, t_env_list *p_list)
{
	if (!buf || !p_list)
		return ;
	return ;
}
