/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:39:03 by sohan             #+#    #+#             */
/*   Updated: 2022/06/27 22:51:28 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../shell/shell.h"
#include "../utils/fd_utils_01.h"
#include "../parse/shell_parse.h"
#include "../init/shell_parse_init.h"
#include "../libft/libft.h"
#include <readline/readline.h>
#include "heredoc.h"
#include "../signal/signal.h"
#include <fcntl.h>
#include "../parse/shell_parse_util_tree2.h"
#include "../utils/state_machine_utils_01.h"
#include "../utils/error_msg_utils_01.h"
#include <errno.h>

int	heredoc(t_shell_data *p_data, const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (-1 == fd)
	{
		ft_perror_param((const char *)0, filename, errno);
		p_data->fileio_errno = 1;
		return (-1);
	}
	p_data->fd_new[IN] = fd;
	ft_dup2(fd, STDIN_FILENO);
	ft_close(fd);
	return (1);
}

int	heredoc_quit(t_shell_data *p_data, char *line)
{
	shell_parse_free(p_data);
	shell_parse_init(p_data);
	ft_set_status(p_data, S_LINE_READ);
	g_data.heredoc_quit = 0;
	p_data->pipe_count = 0;
	free(line);
	dup2(p_data->cp_stdin, STDIN_FILENO);
	return (1);
}

int	heredoc_readline(t_shell_data *p_data, \
										const char *filename, const char *eof)
{
	char	*line;
	int		fd;

	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (-1);
	while (1)
	{
		heredoc_is_running();
		line = readline("> ");
		if (g_data.heredoc_quit)
			return (heredoc_quit(p_data, line));
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
	char					*filename;

	node = p_data->heredoc_list.head.next;
	while (node != &p_data->heredoc_list.tail)
	{
		filename = make_heredoc_filename(&p_data->heredoc_cnt);
		if (NULL == filename)
			return (-1);
		result = heredoc_readline(p_data, filename, node->delimiter);
		free(filename);
		if (result == -1)
		{
			ft_set_status(p_data, S_ERROR);
			return (-1);
		}
		else if (result == 1)
			return (-1);
		node = node->next;
	}
	return (1);
}
