/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_interface_02.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:08:44 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 12:48:16 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_LIST_INTERFACE_02_H
# define ENV_LIST_INTERFACE_02_H
# include "env_list.h"

int	env_node_delete(t_env_list *p_list, const char *p_key);
int	env_node_replace(t_env_list *p_list, char *p_key, char *p_value);

#endif
