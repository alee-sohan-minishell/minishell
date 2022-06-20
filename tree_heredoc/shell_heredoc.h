/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_heredoc.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:57:07 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/20 19:33:24 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_HEREDOC_H
# define SHELL_HEREDOC_H

typedef struct s_shell_heredoc_node
{
	struct s_shell_heredoc_node	*next;
	struct s_shell_heredoc_node	*pre;
	char						*delimiter;
}	t_shell_heredoc_node;

typedef struct s_shell_heredoc_list
{
	struct s_shell_heredoc_node	head;
	struct s_shell_heredoc_node	tail;
}	t_shell_heredoc_list;

t_shell_heredoc_node	*heredoc_new_node(char *delimiter);
void					heredoc_node_free(t_shell_heredoc_node *node);
void					heredoc_list_free(t_shell_heredoc_list *list);
void					heredoc_list_add(t_shell_heredoc_list *list,
							t_shell_heredoc_node *node);

#endif
