/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 04:31:16 by alee              #+#    #+#             */
/*   Updated: 2022/05/16 05:37:35 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../shell/shell.h"
#include "../libft/libft.h"
#include "../utils/utils_01.h"
#include "../utils/utils_02.h"
#include <unistd.h>
#include "shell_init.h"

void	shell_init(t_shell_data *p_data, int argc, char **argv[], char **env[])
{
	p_data->prompt_msg = "shell$ ";
	if (arg_init(p_data, argc) == 0)
		return ;
	if (isatty_init(p_data) == 0)
		return ;
	if (set_tc_attr(p_data) == 0)
		return ;
	if (dup_init(p_data) == 0)
		return ;
	p_data->p_argv = argv;
	p_data->p_env = env;//TODO : env -> data insert in tree
	ft_set_status(p_data, S_LINE_READ);
	return ;
}

int	arg_init(t_shell_data *p_data, int argc)
{
	if (argc != 1)
	{
		ft_putendl_fd("Invaild argc", STDOUT_FILENO);
		ft_set_status(p_data, S_CLOSE);
		return (0);
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
		return (0);
	}
	return (1);
}

int	set_tc_attr(t_shell_data *p_data)
{
	if (tcgetattr(STDOUT_FILENO, &p_data->default_term_attr) == 0)
	{
		p_data->new_term_attr = p_data->default_term_attr;
		p_data->new_term_attr.c_lflag &= (~ECHOCTL);
	}
	else
	{
		ft_set_status(p_data, S_ERROR);
		return (0);
	}
	return (1);
}

int		dup_init(t_shell_data *p_data)
{
	p_data->cp_stdin = ft_dup(STDIN_FILENO);
	if (p_data->cp_stdin == -1)
	{
		ft_set_status(p_data, S_ERROR);
		return (0);
	}
	p_data->cp_stdout = ft_dup(STDOUT_FILENO);
	if (p_data->cp_stdout == -1)
	{
		close(p_data->cp_stdin);
		ft_set_status(p_data, S_ERROR);
		return (0);
	}
	p_data->cp_stderr = ft_dup(STDERR_FILENO);
	if (p_data->cp_stderr == -1)
	{
		close(p_data->cp_stdout);
		close(p_data->cp_stdin);
		ft_set_status(p_data, S_ERROR);
		return (0);
	}
	return (1);
}
