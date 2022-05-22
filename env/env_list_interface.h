/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_interface.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 19:53:33 by alee              #+#    #+#             */
/*   Updated: 2022/05/22 20:35:11 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_LIST_INTERFACE_H
# define ENV_LIST_INTERFACE_H
# include "env_list.h"

t_env_node	*env_node_create(void);
int			env_node_add_back(t_env_list *p_list, t_env_node *p_new_node);
int			env_node_add_front(t_env_list *p_list, t_env_node *p_new_node);
int			env_node_search(t_env_list *p_list, const char *key, \
												t_env_node **o_node);
int			env_node_clear(t_env_list *p_list);

#endif
