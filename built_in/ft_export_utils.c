/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:39:50 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 16:25:11 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env_list.h"
#include <stdlib.h>
#include "../libft/libft.h"
#include "ft_export_utils.h"

int	malloc_export_buffer(char ***buf, t_env_list *p_list, int *o_buf_count)
{
	t_env_node	*cur_node;
	int			idx[2];

	if (!buf)
		return (0);
	*buf = (char **)malloc(sizeof(char *) * p_list->node_count);
	if (!(*buf))
		return (0);
	cur_node = p_list->dummy_head.next;
	ft_bzero(idx, sizeof(idx));
	while (cur_node != &p_list->dummy_tail)
	{
		idx[1] = ft_strlen(cur_node->key) + export_str_len(cur_node->value);
		(*buf)[idx[0]] = (char *)malloc(++idx[1]);
		if (!((*buf)[idx[0]]))
			return (free_export_buffer(buf, idx[0]));
		(*buf)[idx[0]][0] = '\0';
		ft_strlcat((*buf)[idx[0]], cur_node->key, idx[1]);
		export_string_cat(cur_node->value, *buf, idx[0], idx[1]);
		cur_node = cur_node->next;
		idx[0]++;
	}
	*o_buf_count = idx[0];
	return (1);
}

int	free_export_buffer(char ***buf, int idx)
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

void	sort_export_buffer(char ***buf, int buf_max)
{
	int		idx;
	int		jdx;
	char	*tmp;

	idx = 0;
	while (idx < buf_max - 1)
	{
		jdx = 0;
		while (jdx < buf_max - idx - 1)
		{
			if (ft_strcmp((*buf)[jdx], (*buf)[jdx + 1]) > 0)
			{
				tmp = (*buf)[jdx];
				(*buf)[jdx] = (*buf)[jdx + 1];
				(*buf)[jdx + 1] = tmp;
			}
			jdx++;
		}
		idx++;
	}
	return ;
}

void	export_string_cat(char *p_value, char **buf, int buf_idx, int buf_len)
{
	if (p_value)
	{
		ft_strlcat(buf[buf_idx], "=", buf_len);
		ft_strlcat(buf[buf_idx], "\"", buf_len);
		ft_strlcat(buf[buf_idx], p_value, buf_len);
		ft_strlcat(buf[buf_idx], "\"", buf_len);
	}
	return ;
}

int	export_str_len(char *p_value)
{
	int	ret;

	ret = 0;
	if (p_value)
		ret += ft_strlen("=") + \
		ft_strlen(p_value) + \
		ft_strlen("\"\"");
	return (ret);
}
