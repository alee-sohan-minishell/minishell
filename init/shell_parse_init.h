/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_init.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:19:56 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/20 22:52:50 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_PARSE_INIT_H
# define SHELL_PARSE_INIT_H

# include "../tree_heredoc/shell_tree.h"
# include "../tree_heredoc/shell_heredoc.h"
# include "../parse/shell_parse_node_list.h"

void	shell_tree_init(t_shell_tree_node *node);
void	shell_heredoc_init(t_shell_heredoc_list *list);
void	shell_list_init(t_parse_list *list);
int		shell_parse_init(t_shell_data *p_data);

#endif
