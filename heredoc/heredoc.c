/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:54:18 by alee              #+#    #+#             */
/*   Updated: 2022/06/21 15:39:29 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "../utils/fd_utils_01.h"
#include <unistd.h>
#include "../utils/pipe_utils_01.h"
#include "../libft/libft.h"
#include <readline/readline.h>

#include "../signal/signal.h"

int	heredoc(t_shell_data *p_data, const char *eof)
{
	int	result;
	int	backup_stdout;
	int	heredoc_pipe[2];

	ft_dup2(p_data->cp_stdin, STDIN_FILENO);
	backup_stdout = ft_dup(STDOUT_FILENO);
	ft_dup2(p_data->cp_stdout, STDOUT_FILENO);
	ft_pipe(heredoc_pipe);
	// result = heredoc_readline(p_data, heredoc_pipe, p_data->heredoc_list->head.delimiter);
	result = heredoc_readline(p_data, heredoc_pipe, eof);
	ft_dup2(backup_stdout, STDOUT_FILENO);
	ft_close(backup_stdout);
	ft_dup2(heredoc_pipe[0], STDIN_FILENO);
	ft_close(heredoc_pipe[1]);
	ft_close(heredoc_pipe[0]);
	return (result);
}

int	heredoc_readline(t_shell_data *p_data, int *heredoc_pipe, const char *eof)
{
	char	*line;

	(void)p_data;
	while (1)
	{
		set_signal_background();
		line = readline("> ");
		if (!line)
		{
			printf("[!line] \n");
			ft_close(heredoc_pipe[0]);
			ft_close(heredoc_pipe[1]);
			return (1);
		}
		if (ft_strcmp(line, eof) == 0)
		{
			printf("[eof match] \n");
			free(line);
			break ;
		}
		ft_putendl_fd(line, heredoc_pipe[1]);
		free(line);
	}
	return (0);
}
