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

typedef enum e_shell_tree_kind
{
	T_EMPTY,
	T_STRING,
	T_INT,
	T_COMMAND,
	T_PIPE,
	T_BOOL_AND,
	T_BOOL_OR,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_REDIRECT_HEREDOC,
	T_REDIRECT_APPEND,
}	t_shell_tree_kind;

typedef struct s_shell_tree_node
{
	enum e_shell_tree_kind		kind;
	struct s_shell_tree_node	*parent;
	struct s_shell_tree_node	*left;
	struct s_shell_tree_node	*right;
	char						**argv;
	int							fd;
	char						*filepath;
}	t_shell_tree_node;

typedef struct s_shell_heredoc_node
{
	struct s_shell_heredoc_node	*next;
	char						*delimiter;
	int							cnt; //#
}	t_shell_heredoc_node;

t_shell_tree_node	*tree_new_node(t_shell_tree_kind kind, char **argv,
						char *filepath);
void				tree_insert(t_shell_tree_node *parent,
						t_shell_tree_node *child);
void				tree_delete(t_shell_tree_node *tree);

#endif
