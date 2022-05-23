#include "../shell/shell.h"
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

static void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{	
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
		(void)signo;
	}
}

void	set_signal_handler()
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_default()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
