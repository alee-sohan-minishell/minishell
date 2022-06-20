/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_util_node_list.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:34:47 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/20 23:41:56 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_PARSE_UTIL_NODE_LIST_H
# define SHELL_PARSE_UTIL_NODE_LIST_H

# include "../shell/shell.h"
# include "shell_parse_node_list.h"

int		shell_parse_node_add_char(t_parse_node *node, char c);
char	*shell_parse_node_to_str(t_parse_node *node); // 원래 node free
char	**shell_parse_list_to_argv(t_parse_list *list); // 원래 list free
void	shell_parse_util_argv_free(char **argv, int cnt);
int		shell_parse_find_str_in_env(t_shell_data *p_data); // p_data->parse_env에 있는 문자 key로 env 찾아서 p_data->parse_tmp에 바로 add_char 함

#endif
