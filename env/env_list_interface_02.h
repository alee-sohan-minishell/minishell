/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_interface_02.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:08:44 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 01:15:44 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_LIST_INTERFACE_02_H
# define ENV_LIST_INTERFACE_02_H
# include "env_list.h"

int	env_node_delete(t_env_list *p_list, const char *key);

#endif
