#include "../shell/shell.h"
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

static void	while_background_handler(int signo)
{
	if (signo == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_redisplay();
		(void)signo;
	}
}

void	set_signal_background()
{
	signal(SIGINT, while_background_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	while_foreground_handler(int signo)
{
	if (signo == SIGINT)
		write(1, "\n", 1);
	if (signo == SIGQUIT)
		write(1, "Quit: 3\n", 8);
}

void	set_signal_foreground()
{
	signal(SIGINT, while_foreground_handler);
	signal(SIGQUIT, while_foreground_handler);
}
