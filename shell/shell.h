/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 01:17:30 by alee              #+#    #+#             */
/*   Updated: 2022/05/30 01:14:55 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

//---------------------------------------
#define DEBUG
#include <stdio.h>
#include "../tree/shell_tree.h"
//---------------------------------------
#include <termios.h>
#include "../env/env_list.h"

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
	char			**cmd; //# 지우고 tree command로 실행해야 할 듯
	// tree
	t_shell_tree_node	*cmd_tree;

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
	int				process_exit_status;
	int				cmd_count;
	int				pfds[2];
	int				is_piped;
	
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

}	t_shell_data;

#endif
