/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 04:41:18 by alee              #+#    #+#             */
/*   Updated: 2022/05/21 15:02:03 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell/shell.h"
#include "libft/libft.h"
#include "logo/logo.h"
#include "init/shell_init.h"
#include "read_line/shell_readline.h"

int	main(int argc, char *argv[], char *env[])
{
	t_shell_data	shell;

	ft_bzero(&shell, sizeof(shell));
	while (1)
	{
		if (shell.status == S_START)
			display_logo(&shell);
		else if (shell.status == S_INIT)
			shell_init(&shell, argc, &argv, &env);
		else if (shell.status == S_LINE_READ)
			shell_readline(&shell);
		// else if (shell.status == S_CMD)
		else if (shell.status == S_CLOSE || shell.status == S_ERROR)
			break ;
	}
	return (shell.last_status);
}
