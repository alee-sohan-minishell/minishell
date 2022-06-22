/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:36:50 by alee              #+#    #+#             */
/*   Updated: 2022/06/22 17:27:55 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H
# include "../shell/shell.h"
# include "../tree_heredoc/shell_tree.h"

int	heredoc(t_shell_data *p_data, const char *eof);
int	heredoc_readline(int *heredoc_pipe, const char *eof);

#endif