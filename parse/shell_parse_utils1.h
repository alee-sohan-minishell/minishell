/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shel_parse_utils1.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:34:47 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/12 10:58:29 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_PARSE_UTILS1_H
# define SHELL_PARSE_UTILS1_H

# include "../parse/shell_parse_state.h"

# define SHELL_PARSE_NODE_SIZE 256

typedef struct s_parse_node
{
	int					cnt;
	int					size;
	char				*str;
	struct s_parse_node	*next;
}	t_parse_node;

typedef struct s_parse_list
{
	int					cnt;
	struct s_parse_node	head; // dummy node
	struct s_parse_node	*tail;// dummy node 아님
}	t_parse_list;

t_state_shell_parse	shell_parse_util_get_state(char c);
void				shell_prase_util_init(t_parse_list *list);
t_parse_node		*shell_parse_util_append_new_node(t_parse_list *list);
int					shell_parse_util_add_char(t_parse_list *list, char c);
char				**shell_parse_util_list_to_argv(t_parse_list *list);


#endif
