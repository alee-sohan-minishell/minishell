/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 02:51:07 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 15:54:57 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env_list.h"
#include "../utils/command_utils_01.h"
#include <unistd.h>
#include "../utils/string_utils_01.h"
#include "ft_export_utils.h"
#include "../utils/error_msg_utils_01.h"
#include "../libft/libft.h"
#include "../env/env_list_interface_02.h"
#include "ft_export.h"

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

int	add_export(char **cmd, t_env_list *p_list)
{
	int		ret;
	int		idx;
	char	*o_key;
	char	*o_value;

	if (!cmd || !p_list)
		return (1);
	ret = 0;
	idx = 0;
	o_key = (char *)0;
	while (cmd[idx])
	{
		if (is_variable_rule(cmd[idx][0]) == 0)
		{
			ft_self_perror_param("export", cmd[idx], "not a valid identifier");
			ret = 1;
		}
		else
		{
			extract_key_value(cmd[idx], &o_key, &o_value);
			env_node_replace(p_list, o_key, o_value);
		}
		idx++;
	}
	return (ret);
}

int	extract_key_value(char *line, char **o_key, char **o_value)
{
	int	vk_len[2];

	if (!line || !o_key || !o_value)
		return (0);
	if (ft_strchr(line, '=') == (char *)0)
	{
		*o_key = ft_strdup(line);
		*o_value = (char *)0;
	}
	else
	{
		vk_len[0] = ft_strlen(line) - ft_strlen(ft_strchr(line, '='));
		vk_len[1] = ft_strlen(line) - (vk_len[0] + 1);
		*o_key = ft_strndup(line, vk_len[0]);
		*o_value = ft_strndup(ft_strchr(line, '=') + 1, vk_len[1]);
	}
	return (1);
}
