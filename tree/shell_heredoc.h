/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_heredoc.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:57:07 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/01 21:19:34 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_HEREDOC_H
# define SHELL_HEREDOC_H

typedef struct s_shell_heredoc_node
{
	struct s_shell_heredoc_node	*next;
	char						*delimiter;
}	t_shell_heredoc_node;

t_shell_heredoc_node	*heredoc_new_node(char *delimiter);
void					heredoc_insert(t_shell_heredoc_node **focus,
							t_shell_heredoc_node *item);
void					heredoc_delete(t_shell_heredoc_node *heredoc);

#endif
