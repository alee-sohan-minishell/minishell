/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 04:41:18 by alee              #+#    #+#             */
/*   Updated: 2022/06/28 02:32:56 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell/shell.h"
#include "libft/libft.h"
#include "logo/logo.h"
#include "init/shell_init.h"
#include "read_line/shell_readline.h"
#include "utils/state_machine_utils_01.h"
#include "parse/shell_parse.h"
#include "excute/shell_excute.h"
#include "heredoc/heredoc.h"
#include "print.h"

int	main(int argc, char *argv[], char *env[])
{
	t_shell_data	shell;
	if (argc == 3)
		printf("%d [%s] \n", argc, argv[1]);
	ft_bzero(&shell, sizeof(shell));
	while (1)
	{
		if (shell.status == S_START)
			display_logo(&shell);
		else if (shell.status == S_INIT)
			shell_init(&shell, argc, &argv, &env);
		else if (shell.status == S_LINE_READ)
			shell_readline(&shell);
		else if (shell.status == S_PARSE)
			shell_parse(&shell);
		else if (shell.status == S_CMD)
		{
			if (shell.heredoc_list.cnt != 0)
				if (heredoc_input(&shell) == -1)
					continue ;
			shell_execute_tree(&shell);
		}
		else if (shell.status == S_CLOSE || shell.status == S_ERROR)
			break ;
	}
	status_close(&shell);
	return (shell.last_status);
}
