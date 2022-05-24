/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 04:31:16 by alee              #+#    #+#             */
/*   Updated: 2022/05/23 18:13:34 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "../libft/libft.h"
#include "../utils/utils_01.h"
#include "../utils/utils_02.h"
#include <unistd.h>
#include "shell_init.h"
#include "../env/env_list.h"
#include "../env/env_utils_01.h"

//debug
#include <stdio.h>

void	shell_init(t_shell_data *p_data, int argc, char **argv[], char **env[])
{
	p_data->prompt_msg = "shell$ ";
	if (arg_init(p_data, argc, env) == -1)
		return ;
	if (isatty_init(p_data) == -1)
		return ;
	if (set_tc_attr(p_data) == -1)
		return ;
	if (dup_init(p_data) == -1)
		return ;
	if (env_init(p_data, env) == -1)
		return ;
	p_data->p_argv = argv;
	ft_set_status(p_data, S_LINE_READ);
	return ;
}

int	arg_init(t_shell_data *p_data, int argc, char **env[])
{
	if (argc != 1)
	{
		ft_putendl_fd("Invaild argc", STDOUT_FILENO);
		ft_set_status(p_data, S_CLOSE);
		return (-1);
	}
	if (!p_data)
	{
		ft_putendl_fd("Invaild shell data", STDOUT_FILENO);
		ft_set_status(p_data, S_CLOSE);
		return (-1);
	}
	if (!env || !(*env))
	{
		ft_putendl_fd("Invaild env", STDOUT_FILENO);
		ft_set_status(p_data, S_CLOSE);
		return (-1);
	}
	return (1);
}

int	isatty_init(t_shell_data *p_data)
{
	p_data->term_status = isatty(STDOUT_FILENO) \
					&& isatty(STDIN_FILENO) \
					&& isatty(STDERR_FILENO);
	if (p_data->term_status == 0)
	{
		ft_putendl_fd("Invalid terminal status", STDOUT_FILENO);
		ft_set_status(p_data, S_ERROR);
		return (-1);
	}
	return (1);
}

int	set_tc_attr(t_shell_data *p_data)
{
	if (tcgetattr(STDOUT_FILENO, &p_data->default_term_attr) == 0)
	{
		p_data->new_term_attr = p_data->default_term_attr;
		p_data->new_term_attr.c_lflag &= (~ECHOCTL);
		tcsetattr(STDOUT_FILENO, TCSANOW, &p_data->new_term_attr);
	}
	else
	{
		ft_set_status(p_data, S_ERROR);
		return (-1);
	}
	return (1);
}

int	set_tc_attr_to_default(t_shell_data *p_data)
{
	tcsetattr(STDOUT_FILENO, TCSANOW, &p_data->default_term_attr);
	return (0);
}

int		dup_init(t_shell_data *p_data)
{
	p_data->cp_stdin = ft_dup(STDIN_FILENO);
	if (p_data->cp_stdin == -1)
	{
		ft_set_status(p_data, S_ERROR);
		return (-1);
	}
	p_data->cp_stdout = ft_dup(STDOUT_FILENO);
	if (p_data->cp_stdout == -1)
	{
		close(p_data->cp_stdin);
		ft_set_status(p_data, S_ERROR);
		return (-1);
	}
	p_data->cp_stderr = ft_dup(STDERR_FILENO);
	if (p_data->cp_stderr == -1)
	{
		close(p_data->cp_stdout);
		close(p_data->cp_stdin);
		ft_set_status(p_data, S_ERROR);
		return (-1);
	}
	return (1);
}

int		env_init(t_shell_data *p_data, char **env[])
{
	int	env_count;

	if (is_env_form(env, &env_count) == 0)
	{
		ft_set_status(p_data, S_ERROR);
		return (-1);
	}
	if (env_set(p_data, env_count, env) == 0)
	{
		ft_set_status(p_data, S_ERROR);
		return (-1);
	}
	if (is_default_home(&p_data->env_list, &p_data->env_default_home) == 0)
		ft_msg_exit("HOME not set", 1, STDOUT_FILENO);

	return (1);
}
