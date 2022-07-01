/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_execute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:09:42 by alee              #+#    #+#             */
/*   Updated: 2022/06/29 18:25:55 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_EXECUTE_H
# define SHELL_EXECUTE_H
# include "../shell/shell.h"

void	shell_execute_tree(t_shell_data *p_data);
void	shell_execute_command_name(t_shell_data *p_data);
void	tree_traverse_execute(t_shell_data *p_data, \
												t_shell_tree_node *cmd_tree);

void	set_io_parent(t_shell_data *p_data, int fd[]);
void	set_io_child(t_shell_data *p_data, int fd[]);

#endif
