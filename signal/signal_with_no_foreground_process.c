/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_with_no_foreground_process.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:11:38 by sohan             #+#    #+#             */
/*   Updated: 2022/06/29 18:27:46 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include "../shell/shell.h"
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>

static void	no_foreground_process_handler(int signo)
{
	if (signo == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_redisplay();
		(void)signo;
		g_exit_code = 1;
	}
}

void	no_foreground_process(void)
{
	signal(SIGINT, no_foreground_process_handler);
	signal(SIGQUIT, SIG_IGN);
}
