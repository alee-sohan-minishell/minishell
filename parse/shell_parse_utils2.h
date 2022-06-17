/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_utils2.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:34:47 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/12 10:58:29 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_PARSE_UTILS2_H
# define SHELL_PARSE_UTILS2_H

# include "../parse/shell_parse_utils1.h"

t_parse_node	*shell_parse_util_append_node_list(t_parse_node **node,
						t_parse_list *list);
void			shell_parse_util_free_node(t_parse_node **node);
void			shell_parse_util_free_list(t_parse_list *list);
int				shell_parse_util_free_argv(char **argv, int cnt);

#endif
