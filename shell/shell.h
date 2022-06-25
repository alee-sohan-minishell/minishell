/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 01:17:30 by alee              #+#    #+#             */
/*   Updated: 2022/06/25 23:16:04 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

//---------------------------------------
#define DEBUG
#include <stdio.h>
//---------------------------------------
#include <termios.h>
#include "../env/env_list.h"
#include "../tree_heredoc/shell_tree.h"
#include "../tree_heredoc/shell_heredoc.h"
#include "../parse/shell_parse_node_list.h"

#define STR_SHELL "shell"

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
	//status
	t_shell_status	status;

	//prompt msg
	char			*prompt_msg;

	//status value
	int				last_status;

	//stdin, stdout, stderr
	int				term_status;
	int				cp_stdin;
	int				cp_stdout;
	int				cp_stderr;

	//command line
	char			*line;
	//command array
	char			**cmd; // TODO: 지우고 tree command로 실행해야 할 듯

	// fd
	int				fd_in_old;
	int				fd_out_old;
	int				fd_in_new;
	int				fd_out_new;
	int				(*pipe_fd)[2];
	int				pipe_count;
	int				pipe_index;
	int				pipe_num;
	t_data			global_data;
	unsigned char	exit_code;
	int				process_exit_status;
	int				cmd_count;
	int				pfds[2];
	int				is_piped;
	int				is_fileio_success;

	//terminal attr
	struct termios	default_term_attr;
	struct termios	new_term_attr;

	//argv
	char		***p_argv;
	char		***p_env;

	//env list
	t_env_list	env_list;
	char		*env_default_home;

	//parse
	struct s_shell_tree_node	tree; // root 더미노드
	struct s_shell_heredoc_list	heredoc_list;
	int							heredoc_cnt;
	struct s_shell_tree_node	*focus; // 처음에 root 더미노드를 가리킴
	struct s_parse_list			parse_list; // argv임시 저장, 실제 파싱된 argv는 tree_node에 저장됨
	struct s_parse_node			*parse_tmp; // parsing하기 위한 임시저장 node, 일반 문자와 redirect가 여기 임시로 저장됨
	struct s_parse_node			*parse_env; // env를 parsing하기 위한 임시저장 node
	t_shell_tree_kind			redirect_kind;
}	t_shell_data;

#endif
