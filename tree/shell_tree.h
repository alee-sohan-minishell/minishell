/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_tree.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:57:07 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/18 06:22:43 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_TREE_H
# define SHELL_TREE_H
# include "../shell/shell.h"

typedef enum e_shell_tree_kind
{
	T_ROOT,
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

t_shell_tree_node	*tree_new_node(t_shell_tree_kind kind, char **argv, int fd,
						char *filepath);
int					tree_append(t_shell_tree_node **p_focus,
						t_shell_tree_node *item);
void				tree_find_append_argv(t_shell_tree_node *focus,
						char **argv); // TODO
int					tree_delete(t_shell_tree_node *tree);
int					is_redirect(t_shell_tree_kind kind);

#endif
