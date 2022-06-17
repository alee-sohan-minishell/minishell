/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_state.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:07:44 by alee              #+#    #+#             */
/*   Updated: 2022/06/05 16:57:45 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_PARSE_STATE_H
# define SHELL_PARSE_STATE_H
# include "../shell/shell.h"

typedef enum e_state_shell_parse
{
	S_P_ERROR = -1,
	S_P_SPACE,
	S_P_QUOTE,
	S_P_DQUOTE,
	S_P_ENV,

	S_P_OPEN,
	S_P_CLOSE,
	S_P_AND,
	S_P_PIPE,
	S_P_REDIRECT_IN,
	S_P_REDIRECT_OUT,

	S_P_BOOL_AND,
	S_P_BOOL_OR,
	S_P_REDIRECT_HEREDOC,
	S_P_REDIRECT_APPEND,
	S_P_DQUOTE_ENV,
	S_P_REDIRECT_SPACE,

	S_P_STRING,
}	t_state_shell_parse;

/*
* shell_parse_state.c
*/
t_state_shell_parse	shell_parse_state1(t_state_shell_parse state,
			t_shell_data *p_data, char c);
t_state_shell_parse	shell_parse_state2(t_state_shell_parse state,
			t_shell_data *p_data, char c);
t_state_shell_parse	shell_parse_state3(t_state_shell_parse state,
			t_shell_data *p_data, char c);
t_state_shell_parse	shell_parse_state4(t_state_shell_parse state,
			t_shell_data *p_data, char c);

/*
* shell_parse_state1.c
*/
t_state_shell_parse	shell_parse_space(t_shell_data *p_data, char c);
t_state_shell_parse	shell_parse_quote(t_shell_data *p_data, char c);
t_state_shell_parse	shell_parse_dquote(t_shell_data *p_data, char c);
t_state_shell_parse	shell_parse_env(t_shell_data *p_data, char c);
t_state_shell_parse	shell_parse_dquote_env(t_shell_data *p_data, char c);

/*
* shell_parse_state2.c
*/
t_state_shell_parse	shell_parse_open(t_shell_data *p_data, char c);
t_state_shell_parse	shell_parse_close(t_shell_data *p_data, char c);
t_state_shell_parse	shell_parse_redirect_space(t_shell_data *p_data, char c);

/*
* shell_parse_state3.c
*/
t_state_shell_parse	shell_parse_and(t_shell_data *p_data, char c);
t_state_shell_parse	shell_parse_pipe(t_shell_data *p_data, char c);
t_state_shell_parse	shell_parse_redirect_in(t_shell_data *p_data, char c);
t_state_shell_parse	shell_parse_redirect_out(t_shell_data *p_data, char c);

/*
* shell_parse_state4.c
*/
t_state_shell_parse	shell_parse_bool_and(t_shell_data *p_data, char c);
t_state_shell_parse	shell_parse_bool_or(t_shell_data *p_data, char c);
t_state_shell_parse	shell_parse_redirect_heredoc(t_shell_data *p_data, char c);
t_state_shell_parse	shell_parse_redirect_append(t_shell_data *p_data, char c);
t_state_shell_parse	shell_parse_string(t_shell_data *p_data, char c);

#endif
