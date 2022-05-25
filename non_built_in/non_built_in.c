/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:38:42 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 18:38:43 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init/shell_init.h"
#include "../signal/signal.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "../init/shell_utils_01.h"
#include "../env/env_list_interface_01.h"

int	ft_exec_command(t_shell_data *p_data)
{
	pid_t	pid;
	char	path[500];
	char	*exec_path;
	int		index;

	exec_path = NULL;
	path[0] = '\0';
	index = 0;
	pid = fork();
	set_signal_foreground();

	//debug
	t_env_node	*cur_node;

	env_node_search(&p_data->env_list, "PATH", &cur_node);
	char **cmd_list = ft_split(cur_node->value, ':');
	int	idx;

	idx = 0;
	if (pid == 0)
	{
		set_tc_attr_to_default(p_data);
		while (cmd_list[idx])
		{
			ft_strlcpy(path, cmd_list[idx], 500);
			ft_strlcat(path, "/", 500);
			exec_path = ft_strjoin(path, p_data->cmd[0]);
			if (execve(exec_path, p_data->cmd, NULL) == -1)
			{
				printf("bash: %s: %s\n", p_data->cmd[0], strerror(errno));
				exit(errno);
			}
			idx++;
		}
		printf("no exist command \n");
	}
	wait(&pid);
	free(exec_path);
	return (0);
}
