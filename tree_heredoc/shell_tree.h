/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_tree.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 00:57:07 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/21 22:54:26 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_TREE_H
# define SHELL_TREE_H

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
void				tree_free(t_shell_tree_node *tree, int filepath); // tree root가 dummy인 걸 고려한 free
void				tree_append(t_shell_tree_node **p_focus,
						t_shell_tree_node *item);
void				shell_tree_insert_push_child(t_shell_tree_node **p_focus,
						t_shell_tree_node *item, int push_left,
						int append_left);
void				shell_tree_insert_push_focus(t_shell_tree_node **p_focus,
						t_shell_tree_node *item, int push_left);

#endif
