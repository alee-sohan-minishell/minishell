/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:39:03 by alee              #+#    #+#             */
/*   Updated: 2022/06/22 19:26:16 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "../utils/fd_utils_01.h"
#include "../libft/libft.h"
#include <readline/readline.h>
#include "heredoc.h"
#include "../signal/signal.h"

int	heredoc(t_shell_data *p_data, const char *eof)
{
	int	result;
	int	stdout_backup;
	int	heredoc_pipe[2];

	ft_dup2(p_data->cp_stdin, STDIN_FILENO);
	stdout_backup = ft_dup(STDOUT_FILENO);
	ft_dup2(p_data->cp_stdout, STDOUT_FILENO);
	ft_pipe(heredoc_pipe);
	result = heredoc_readline(heredoc_pipe, eof);
	ft_dup2(stdout_backup, STDOUT_FILENO);
	ft_close(stdout_backup);
	ft_dup2(heredoc_pipe[0], STDIN_FILENO);
	ft_close(heredoc_pipe[1]);
	ft_close(heredoc_pipe[0]);
	return (result);
}

int	heredoc_readline(int *heredoc_pipe, const char *eof)
{
	char	*line;

	while (1)
	{
		set_signal_background();
		line = readline("> ");
		if (!line)
		{
			ft_close(heredoc_pipe[0]);
			ft_close(heredoc_pipe[1]);
			return (1);
		}
		if (ft_strcmp(line, eof) == 0 || line[0] == 10)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, heredoc_pipe[1]);
		free(line);
	}
	return (0);
}
