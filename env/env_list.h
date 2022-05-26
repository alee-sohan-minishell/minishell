/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 12:44:27 by alee              #+#    #+#             */
/*   Updated: 2022/05/26 13:55:23 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_LIST_H
# define ENV_LIST_H

typedef struct s_env_node	t_env_node;

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

int			env_list_init(t_env_list *p_list);

#endif
