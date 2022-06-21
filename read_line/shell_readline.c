/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 05:40:09 by alee              #+#    #+#             */
/*   Updated: 2022/06/17 19:26:11 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "../signal/signal.h"
#include <readline/readline.h>
#include "../libft/libft.h"
#include "../utils/state_machine_utils_01.h"
#include <readline/history.h>
#include "shell_readline.h"
#include "../init/shell_utils_01.h"

void	shell_readline(t_shell_data *p_data)
{
	set_signal_background();
	p_data->line = readline(p_data->prompt_msg);
	if (!p_data->line)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		ft_set_status(p_data, S_ERROR);
		set_tc_attr_to_default(p_data);
		return ;
	}
	/*	ADD HISTORY	*/
	insert_cmd_history(p_data->line);
	/*	Set Status	*/
	ft_set_status(p_data, S_PARSE);
	return ;
}

void	insert_cmd_history(const char *cmd)
{
	if (cmd[0] != '\0')
		add_history(cmd);
	return ;
}

//파싱, 트리구조(추상구문트리),

//alee : 빌트인, env, export, unset

//min-jo : tree, redirection, pipe, heredoc

//sohan : Unit test, parsing
