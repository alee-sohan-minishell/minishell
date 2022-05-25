/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 02:51:07 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 12:15:05 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "../utils/command_utils_01.h"
#include "../libft/libft.h"
#include "ft_export.h"
#include <unistd.h>
#include "../utils/error_msg_utils_01.h"
#include "../utils/string_utils_01.h"
#include "../env/env_list_interface_01.h"

int	ft_export(char **cmd, t_env_list *p_list)
{
	if (!cmd || !(*cmd) || !p_list)
		return (1);
	if (get_cmd_count(cmd) > 1)
		return (add_export(&cmd[1], p_list));
	else
		print_export(p_list);
	return (0);
}

void	print_export(t_env_list *p_list)
{
	char	**buf;
	int		str_count;

	if (malloc_export_buffer(&buf, p_list, &str_count) == 0)
		ft_msg_exit("Export malloc Failed \n", 1, STDERR_FILENO);
	sort_export_buffer(&buf, str_count);
	print_export_buffer(&buf, str_count);
	free_export_buffer(&buf, str_count);
	return ;
}


int		malloc_export_buffer(char ***buf, t_env_list *p_list, int *o_buf_count)
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
			buf_len += ft_strlen("=") + ft_strlen(cur_node->value) + ft_strlen("\"\"");
		(*buf)[idx] = (char *)malloc(++buf_len);
		if (!((*buf)[idx]))
			return (free_export_buffer(buf, idx));
		(*buf)[idx][0] = '\0';
		ft_strlcat((*buf)[idx], cur_node->key, buf_len);
		if (cur_node->value)
		{
			ft_strlcat((*buf)[idx], "=", buf_len);
			ft_strlcat((*buf)[idx], "\"", buf_len);
			ft_strlcat((*buf)[idx], cur_node->value, buf_len);
			ft_strlcat((*buf)[idx], "\"", buf_len);
		}
		cur_node = cur_node->next;
		idx++;
	}
	*o_buf_count = idx;
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

void	print_export_buffer(char ***buf, int buf_max)
{
	int	idx;

	idx = 0;
	while (idx < buf_max)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd((*buf)[idx], STDOUT_FILENO);
		idx++;
	}
	return ;
}

int		add_export(char **cmd, t_env_list *p_list)
{
	int		ret;
	int		idx;
	char	*o_key;

	if (!cmd || !p_list)
		return (1);
	ret = 0;
	idx = 0;
	o_key = (char *)0;
	while (cmd[idx])
	{
		if (is_variable_rule(cmd[idx][0]) == 0)
		{
			ft_custom_perror_param("export", cmd[idx], "not a valid identifier");
			ret = 1;
		}
		else
		{

		}
		idx++;
	}
	return (ret);
}
