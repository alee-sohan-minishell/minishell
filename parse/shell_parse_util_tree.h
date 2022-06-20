/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_util_tree.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:34:47 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/20 22:20:50 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_PARSE_UTIL_TREE_H
# define SHELL_PARSE_UTIL_TREE_H

# include "../shell/shell.h"
# include "../tree_heredoc/shell_tree.h"

int		shell_parse_util_insert_cmd(t_shell_data *p_data);
void	shell_parse_util_push_tree(t_shell_tree_node **p_focus,
			t_shell_tree_node *item);
int		shell_parse_util_insert_argv_in_cmd(t_shell_tree_node *focus,
			char *str); // focus의 주소가 아닌, focus의 복사본이 들어가야 함

#endif
