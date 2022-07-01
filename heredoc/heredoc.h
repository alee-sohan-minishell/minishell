/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan<sohan@student.42seoul.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:36:50 by sohan             #+#    #+#             */
/*   Updated: 2022/06/26 16:55:12 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H
# include "../shell/shell.h"
# include "../tree_heredoc/shell_tree.h"

int	heredoc(t_shell_data *p_data, const char *eof);
int	heredoc_readline(const char *filename, const char *eof);
int	heredoc_input(t_shell_data *p_data);

#endif
