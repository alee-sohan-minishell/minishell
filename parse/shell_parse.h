/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:07:44 by alee              #+#    #+#             */
/*   Updated: 2022/05/26 12:12:08 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_PARSE_H
# define SHELL_PARSE_H
# include "../shell/shell.h"
# define MAX_LINE_LEN 1024

typedef struct s_token_node t_token_node;
typedef struct s_token_list t_token_list;

enum e_token_type
{
	WORD,
	ASSIGNMENT_WORD,
	NEWLINE,
	IO_NUMBER
};

enum e_metacharacter
{
	META_SPACE,
	META_TAB,
	META_NEWLINE,
	META_PIPE,
	META_REDI_IN,
	META_REDI_OUT,
	META_APPEND,
	META_HEREDOC,
	META_DOLLOR,
};

struct s_token_node
{
	int				type;
	char			*unit;
	t_token_node	*prev;
	t_token_node	*next;
};

struct s_token_list
{
	t_token_node	*head;
	t_token_node	*tail;
	int				size;
};

typedef struct s_stack
{
	int	arr[MAX_LINE_LEN];
	int	size;
}	t_stack;

void	shell_parse(t_shell_data *p_data);

#endif
