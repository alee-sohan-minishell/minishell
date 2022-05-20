/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 02:45:49 by alee              #+#    #+#             */
/*   Updated: 2022/03/05 10:35:43 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		node_size;
	t_list	*cur_node;

	cur_node = lst;
	node_size = 0;
	if (!cur_node)
		return (0);
	node_size++;
	while (cur_node->next)
	{
		node_size++;
		cur_node = cur_node->next;
	}
	return (node_size);
}
