/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_interface_02.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:09:12 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 02:32:52 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"
#include "env_list_interface_01.h"
#include <stdlib.h>

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
