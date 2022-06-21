/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:52:59 by alee              #+#    #+#             */
/*   Updated: 2022/06/21 15:39:37 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H
# include "../shell/shell.h"

int	heredoc(t_shell_data *p_data, const char *eof);
int	heredoc_readline(t_shell_data *p_data, int *heredoc_pipe, const char *eof);

#endif
