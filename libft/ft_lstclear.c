/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan<sohan@student.42seoul.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 04:28:31 by sohan             #+#    #+#             */
/*   Updated: 2022/03/05 10:34:05 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cur_node;
	t_list	*del_node;

	cur_node = (*lst);
	while (cur_node)
	{
		del(cur_node->content);
		del_node = cur_node;
		cur_node = cur_node->next;
		free(del_node);
	}
	(*lst) = cur_node;
	return ;
}
