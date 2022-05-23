/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_interface_01.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 19:53:33 by alee              #+#    #+#             */
/*   Updated: 2022/05/23 12:08:33 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_LIST_INTERFACE_01_H
# define ENV_LIST_INTERFACE_01_H
# include "env_list.h"

t_env_node	*env_node_create(char *p_key, char *p_value);
int			env_node_add_back(t_env_list *p_list, t_env_node *p_new_node);
int			env_node_add_front(t_env_list *p_list, t_env_node *p_new_node);
int			env_node_search(t_env_list *p_list, const char *key, \
												t_env_node **o_node);
int			env_node_clear(t_env_list *p_list);

#endif
