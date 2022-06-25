/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:48:16 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/25 22:45:11 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "init/shell_parse_init.h"
#include "shell/shell.h"
#include "parse/shell_parse.h"
#include "utils/state_machine_utils_01.h"

void	print_recur(t_shell_tree_node *t, int left, int *count)
{
	const char	*which[] = {
		"root", "empty", "string", "int", "cmd",
		"|", "&&", "||", "<", ">", "<<", ">>"};
	int 		cnt = -1;

	printf("%d: tree %s" , (*count)++, which[t->kind]);
	if (t->kind == T_PIPE)
		printf("%d", t->pnum);
	printf(" %d\n", left);
	if (NULL == t->argv)
		printf("	no argv\n");
	else
	{
		while (t->argv[++cnt])
			printf("	%d: %s\n", cnt, t->argv[cnt]);
	}
	if (NULL == t->filepath)
		printf("	no filepath\n");
	else
		printf("	file: %s\n", t->filepath);
	if (t->left)
		print_recur(t->left, 1, count);
	if (t->right)
		print_recur(t->right, 0, count);
	printf("up\n\n");
}

void	print_heredoc(t_shell_data *shell)
{
	t_shell_heredoc_node	*node;
	int						cnt;

	cnt = -1;
	node = shell->heredoc_list.head.next;
	while (node != &shell->heredoc_list.tail)
	{
		printf("%d: heredoc, delimiter: %s\n", ++cnt, node->delimiter);
		node = node->next;
	}
	printf("\n");
}

void	print_tree(t_shell_data *shell)
{
	int	count;

	count = 0;
	print_recur(&shell->tree, 0, &count);
	printf("\n");
	// shell_parse_free(shell);
	// shell->pipe_count = 0;
	// shell_parse_init(shell);
	// ft_set_status(shell, S_LINE_READ);
}
