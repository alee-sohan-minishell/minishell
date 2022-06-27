/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_node_list.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:34:47 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/27 22:48:20 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_PARSE_NODE_LIST_H
# define SHELL_PARSE_NODE_LIST_H

# define SHELL_PARSE_NODE_SIZE 256

typedef struct s_parse_node
{
	int					cnt;
	int					size;
	char				*str;
	struct s_parse_node	*next;
	struct s_parse_node	*pre;
}	t_parse_node;

typedef struct s_parse_list
{
	int					cnt;
	struct s_parse_node	head;
	struct s_parse_node	tail;
}	t_parse_list;

t_parse_node	*shell_parse_new_node(void);
void			shell_parse_node_free(t_parse_node *node);
int				shell_parse_list_append_node(t_parse_list *list,
					t_parse_node **p_node);
void			shell_parse_list_free(t_parse_list *list);

#endif
