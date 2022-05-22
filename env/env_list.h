/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 12:44:27 by alee              #+#    #+#             */
/*   Updated: 2022/05/22 14:09:46 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_LIST_H
# define ENV_LIST_H

typedef struct s_env_node t_env_node;

typedef struct s_env_node
{
	char		*key;
	char		*value;
	t_env_node	*prev;
	t_env_node	*next;
}	t_env_node;

typedef struct s_env_list
{
	int			node_count;
	t_env_node	dummy_head;
	t_env_node	dummy_tail;
}	t_env_list;

/*	Func Init	*/
int			env_list_init(t_env_list	*list);

/*	Func Create	*/
t_env_node	*env_create_node(const char *key, const	char *value);

/*	Func Insert	*/
// int			env_insert_node(t_env_list	*p_list, const char *key, const char *value);
int			env_insert_line(const char *line, t_env_list *p_list);



/*	Func Delete	*/
// int			env_delete_node(void);

/*	Func Clear	*/
/*	Func Search	*/
int			env_search_node(t_env_list *p_list, const char *key, \
												t_env_node **o_node);

/*	Func Write	*/

#endif
