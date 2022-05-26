/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_interface_01.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 19:53:55 by alee              #+#    #+#             */
/*   Updated: 2022/05/26 14:28:48 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"
#include "../libft/libft.h"
#include <unistd.h>

t_env_node	*env_node_create(char *p_key, char *p_value)
{
	t_env_node	*node;

	node = (t_env_node *)malloc(sizeof(t_env_node));
	if (!node || !p_key)
		return ((t_env_node *)0);
	node->key = p_key;
	node->value = p_value;
	node->next = (t_env_node *)0;
	node->prev = (t_env_node *)0;
	return (node);
}

int	env_node_add_front(t_env_list *p_list, t_env_node *p_new_node)
{
	if (!p_new_node || !p_list)
		return (0);
	p_new_node->prev = &p_list->dummy_head;
	p_new_node->next = p_list->dummy_head.next;
	p_list->dummy_head.next->prev = p_new_node;
	p_list->dummy_head.next = p_new_node;
	++p_list->node_count;
	return (1);
}

int	env_node_add_back(t_env_list *p_list, t_env_node *p_new_node)
{
	if (!p_new_node || !p_list)
		return (0);
	p_new_node->next = &p_list->dummy_tail;
	p_new_node->prev = p_list->dummy_tail.prev;
	p_list->dummy_tail.prev->next = p_new_node;
	p_list->dummy_tail.prev = p_new_node;
	++p_list->node_count;
	return (1);
}

int	env_node_search(t_env_list *p_list, const char *key, t_env_node **o_node)
{
	t_env_node	*cur_node;

	if (!p_list || !o_node)
		return (-1);
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

int	env_node_clear(t_env_list *p_list)
{
	t_env_node	*del_node;
	t_env_node	*cur_node;

	if (!p_list)
		return (-1);
	if (p_list->node_count == 0)
		return (-1);
	cur_node = p_list->dummy_head.next;
	while (cur_node != &p_list->dummy_tail)
	{
		if (cur_node->key)
			free(cur_node->key);
		if (cur_node->value)
			free(cur_node->value);
		del_node = cur_node;
		cur_node = cur_node->next;
		free(del_node);
	}
	env_list_init(p_list);
	return (1);
}
