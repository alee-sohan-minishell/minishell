/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 03:57:15 by alee              #+#    #+#             */
/*   Updated: 2022/03/05 10:33:53 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*cur_node;

	cur_node = (*lst);
	if (!cur_node)
	{
		new->next = 0;
		(*lst) = new;
		return ;
	}
	while (cur_node->next)
		cur_node = cur_node->next;
	if (!(new->next))
		new->next = cur_node->next;
	cur_node->next = new;
	return ;
}
