/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 04:59:53 by alee              #+#    #+#             */
/*   Updated: 2022/03/05 10:34:36 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*cur_node;

	if (!f || !lst)
		return ;
	cur_node = lst;
	while (cur_node)
	{
		f(cur_node->content);
		cur_node = cur_node->next;
	}
	return ;
}
