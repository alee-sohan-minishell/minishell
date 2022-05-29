/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_tree.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:57:07 by min-jo            #+#    #+#             */
/*   Updated: 2022/05/30 01:30:28 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_TREE_H
# define SHELL_TREE_H
# include "../shell/shell.h"

typedef enum e_shell_tree_kind
{
	T_EMPTY,
	T_COMMAND,
	T_PIPE,
	T_BOOL,
	T_REDIRECT,
}	s_shell_tree_kind;

typedef struct s_shell_tree_node
{
	enum e_shell_tree_kind		kind;
	struct s_shell_tree_node	*left;
	struct s_shell_tree_node	*right;
	char						**argv;
	char						*filepath;
	int							fd;
}	t_shell_tree_node;

typedef struct s_shell_heredoc_node
{
	struct s_shell_heredoc_node	*next;
	char						*delimiter;
}	t_shell_heredoc_node;

typedef struct s_shell_tree
{
	struct s_shell_tree_node	*root;
	struct s_shell_heredoc_node	*heredoc;
}	t_shell_tree;

#endif
