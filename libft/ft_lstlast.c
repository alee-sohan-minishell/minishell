/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 02:50:40 by alee              #+#    #+#             */
/*   Updated: 2022/03/05 10:34:56 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*cur_node;

	cur_node = lst;
	if (!cur_node)
		return ((t_list *)(0));
	while (cur_node->next)
		cur_node = cur_node->next;
	return (cur_node);
}
