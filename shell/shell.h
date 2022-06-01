/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 01:17:30 by alee              #+#    #+#             */
/*   Updated: 2022/06/11 22:01:47 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

//---------------------------------------
#define DEBUG
#include <stdio.h>
//---------------------------------------
//# 0. // TODO window에서 컴파일 에러 때문에 임시로 지움 다시 되돌려 놔야 함 #include <termios.h>
#include "../env/env_list.h"
#include "../parse/shell_parse_utils1.h"
#include "../tree/shell_tree.h"
#include "../tree/shell_heredoc.h"

#define STR_SHELL "shell"

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
	struct s_shell_heredoc_node	heredoc;
	struct s_shell_tree_node	*focus; // 처음에 root 더미노드를 가리킴
	struct s_parse_list			parse_list; // 임시 저장용, 실제 파싱된 argv는 tree_node에 저장됨
	struct s_parse_node			parse_env; // $env parsing 하기 위한 임시저장 dummy node
}	t_shell_data;

#endif
