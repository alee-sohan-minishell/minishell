/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 01:17:30 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 18:38:00 by alee             ###   ########.fr       */
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
	char			**cmd;

	//terminal attr
	struct termios	default_term_attr;
	struct termios	new_term_attr;

	//argv
	char		***p_argv;
	char		***p_env;

	//env list
	t_env_list	env_list;
	char		*env_default_home;
}	t_shell_data;

#endif
