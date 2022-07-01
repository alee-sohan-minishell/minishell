/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_with_foreground_process.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan<sohan@student.42seoul.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:11:29 by sohan             #+#    #+#             */
/*   Updated: 2022/06/29 18:27:46 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>

static void	shell_command_process_handler(int signo)
{
	if (signo == SIGINT)
		write(1, "\n", 1);
	if (signo == SIGQUIT)
		write(1, "Quit: 3\n", 8);
}

void	shell_command_is_foreground_process(void)
{
	signal(SIGINT, shell_command_process_handler);
	signal(SIGQUIT, shell_command_process_handler);
}

static void	executable_file_process_handler(int signo)
{
	rl_redisplay();
	(void)signo;
}

void	executable_file_is_foreground_process(void)
{
	signal(SIGINT, executable_file_process_handler);
	signal(SIGQUIT, executable_file_process_handler);
}

void	minishell_is_foreground_process(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
