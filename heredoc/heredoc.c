/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:39:03 by alee              #+#    #+#             */
/*   Updated: 2022/06/26 17:25:44 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "../utils/fd_utils_01.h"
#include "../libft/libft.h"
#include <readline/readline.h>
#include "heredoc.h"
#include "../signal/signal.h"
#include <fcntl.h>
#include "../parse/shell_parse_util_tree2.h"
#include "../utils/state_machine_utils_01.h"

int	heredoc(t_shell_data *p_data, const char *filename)
{
	int	stdout_backup;
	int	heredoc_pipe[2];
	int	fd;

	// TODO 여기서는 main문 쪽에서 만든 file을 !!!!!!open!!!!!해서 dup2만 하면됨
	// eof는 지우고, heredoc_readline()은 main 쪽으로 빠져야 됨
	// TODO filename open 하고 그걸 dup2 해야 됨 됨
	filename = NULL; // TODO 컴파일 안돼서 걍 해놓음
	fd = 0;

	ft_dup2(p_data->cp_stdin, STDIN_FILENO);
	stdout_backup = ft_dup(STDOUT_FILENO);
	ft_dup2(p_data->cp_stdout, STDOUT_FILENO);
	ft_pipe(heredoc_pipe);

	ft_dup2(stdout_backup, STDOUT_FILENO);
	ft_close(stdout_backup);
	ft_dup2(heredoc_pipe[0], STDIN_FILENO);
	ft_close(heredoc_pipe[1]);
	ft_close(heredoc_pipe[0]);
	return (1);
}

int	heredoc_readline(const char *filename, const char *eof)
{
	char	*line;
	int		fd;

	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (-1);
	while (1)
	{
		set_signal_background();
		line = readline("> ");
		if (!line)
			return (1);
		if (ft_strcmp(line, eof) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	return (0);
}

int	heredoc_input(t_shell_data *p_data)
{
	t_shell_heredoc_node	*node;
	int						result;

	node = p_data->heredoc_list.head.next;
	while (node != &p_data->heredoc_list.tail)
	{
		result = heredoc_readline(make_heredoc_filename(&p_data->heredoc_cnt), node->delimiter);
		if (result == -1)
		{
			ft_set_status(p_data, S_ERROR);
			return (-1);
		}
		node = node->next;
	}
	return (1);
}
