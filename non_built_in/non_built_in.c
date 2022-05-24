#include "../init/shell_init.h"
#include "../signal/signal.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>

int	ft_exec_command(t_shell_data *p_data)
{
	pid_t	pid;
	char	*path;
	char	*exec_path;
	int		index;

	exec_path = NULL;
	index = 0;
	pid = fork();
	set_signal_foreground();
	if (pid == 0)
	{
		set_tc_attr_to_default(p_data);
		path = "/bin/";
		exec_path = ft_strjoin(path, p_data->cmd[0]);
		if (execve(exec_path, p_data->cmd, NULL) == -1)
		{
			printf("bash: %s: %s\n", p_data->cmd[0], strerror(errno));
			exit(errno);
		}
	}
	wait(&pid);
	while (p_data->cmd[index])
	{
		free(p_data->cmd[index]);
		++index;
	}
	free(p_data->cmd);
	free(exec_path);
	return (0);
}
