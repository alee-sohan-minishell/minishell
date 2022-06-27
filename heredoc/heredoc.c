/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:39:03 by alee              #+#    #+#             */
/*   Updated: 2022/06/27 22:51:28 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../shell/shell.h"
#include "../utils/fd_utils_01.h"
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
	p_data->fd_in_new = fd;
	ft_dup2(fd, STDIN_FILENO);
	ft_close(fd);
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
	char					*filename;

	node = p_data->heredoc_list.head.next;
	while (node != &p_data->heredoc_list.tail)
	{
		filename = make_heredoc_filename(&p_data->heredoc_cnt);
		if (NULL == filename)
			return (-1);
		result = heredoc_readline(filename, node->delimiter);
		free(filename);
		if (result == -1)
		{
			ft_set_status(p_data, S_ERROR);
			return (-1);
		}
		node = node->next;
	}
	return (1);
}
