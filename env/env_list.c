/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 12:50:26 by alee              #+#    #+#             */
/*   Updated: 2022/05/26 13:55:28 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"
#include "../libft/libft.h"

int	env_list_init(t_env_list *p_list)
{
	if (p_list == (t_env_list *)0)
		return (-1);
	ft_bzero(p_list, sizeof(t_env_list));
	p_list->node_count = 0;
	p_list->dummy_head.prev = (t_env_node *)0;
	p_list->dummy_tail.next = (t_env_node *)0;
	p_list->dummy_tail.prev = &p_list->dummy_head;
	p_list->dummy_head.next = &p_list->dummy_tail;
	return (1);
}
