/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_interface_02.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:09:12 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 13:31:32 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"
#include "env_list_interface_01.h"
#include <stdlib.h>
#include "../libft/libft.h"

int	env_node_delete(t_env_list *p_list, const char *key)
{
	t_env_node	*del_node;

	if (env_node_search(p_list, key, &del_node) == 0)
		return (0);
	if (del_node->key)
		free(del_node->key);
	if (del_node->value)
		free(del_node->value);
	del_node->next->prev = del_node->prev;
	del_node->prev->next = del_node->next;
	free(del_node);
	return (1);
}

int	env_node_replace(t_env_list *p_list, char *p_key, char *p_value)
{
	t_env_node	*o_replace_node;

	if (!p_list || !p_key)
		return (0);
	if (env_node_search(p_list, p_key, &o_replace_node))
	{
		free(o_replace_node->key);
		o_replace_node->key = p_key;
		if (o_replace_node->value)
			free(o_replace_node->value);
		if (p_value)
			o_replace_node->value = p_value;
		else
			o_replace_node->value = (char *)0;
	}
	else
		env_node_add_back(p_list, env_node_create(p_key, p_value));
	return (1);
}
