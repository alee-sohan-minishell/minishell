/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 12:50:26 by alee              #+#    #+#             */
/*   Updated: 2022/05/22 14:06:18 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"
#include "../libft/libft.h"

int		env_list_init(t_env_list	*list)
{
	if (list == (t_env_list *)0)
		return (0);
	ft_bzero(list, sizeof(t_env_list));
	list->node_count = 0;
	list->dummy_head.prev = (t_env_node *)0;
	list->dummy_head.next = &list->dummy_tail;
	list->dummy_tail.prev = &list->dummy_head;
	list->dummy_tail.next = (t_env_node *)0;
	return (1);
}

t_env_node	*env_create_node(const char *key, const	char *value)
{
	t_env_node	*node;

	if (key == (const char *)0 || value == (const char *)0)
		return ((t_env_node *)0);
	node = (t_env_node *)malloc(sizeof(t_env_node));
	if (!node)
		return ((t_env_node *)0);
	node->key = (char *)0;
	node->value = (char *)0;
	node->next = (t_env_node *)0;
	node->prev = (t_env_node *)0;
	return (node);
}

int	env_search_node(t_env_list *p_list, const char *key, t_env_node **o_node)
{
	t_env_node	*cur_node;
	
	if (p_list->node_count == 0)
		return (0);
	cur_node = p_list->dummy_head.next;
	while (cur_node != &p_list->dummy_tail)
	{
		if (ft_strcmp(cur_node->key, key) == 0)
		{
			*o_node = cur_node;
			return (1);
		}
		cur_node = cur_node->next;
	}
	return (0);
}