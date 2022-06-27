/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 01:17:30 by alee              #+#    #+#             */
/*   Updated: 2022/06/28 00:23:02 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# define WRITE 1
# define READ 0
# define DEBUG_TREE 0
# define STR_SHELL "shell"
# include <stdio.h>
# include <termios.h>
# include "../env/env_list.h"
# include "../tree_heredoc/shell_tree.h"
# include "../tree_heredoc/shell_heredoc.h"
# include "../parse/shell_parse_node_list.h"

typedef struct s_pipe_data
{
	int		*pipe_status;
	int		signal_status;
	pid_t	*pipe_pid;
	int		index;
}	t_data;

typedef enum e_shell_status
{
	S_START = 0,
	S_INIT,
	S_ERROR,
	S_LINE_READ,
	S_PARSE,
	S_NO_CMD,
	S_CMD,
	S_CLOSE,
}	t_shell_status;

typedef struct s_shell_data
{
	t_shell_status				status;

	char						*prompt_msg;

	int							last_status;

	int							term_status;
	int							cp_stdin;
	int							cp_stdout;
	int							cp_stderr;

	char						*line;

	char						**cmd;

	int							fd_in_old;
	int							fd_out_old;
	int							fd_in_new;
	int							fd_out_new;
	int							(*pipe_fd)[2];
	int							pipe_count;
	int							pipe_index;
	int							pipe_num;
	t_data						global_data;
	unsigned char				exit_code;
	int							process_exit_status;
	int							cmd_count;
	int							pfds[2];
	int							is_piped;
	int							is_fileio_success;
	int							fileio_errno;
	pid_t						pipepid; // TODO

	struct termios				default_term_attr;
	struct termios				new_term_attr;

	char						***p_argv;
	char						***p_env;

	t_env_list					env_list;
	char						*env_default_home;

	struct s_shell_tree_node	tree;
	struct s_shell_heredoc_list	heredoc_list;
	int							heredoc_cnt;
	struct s_shell_tree_node	*focus;
	struct s_parse_list			parse_list;
	struct s_parse_node			*parse_tmp;
	struct s_parse_node			*parse_env;
	t_shell_tree_kind			redirect_kind;
}	t_shell_data;

#endif
