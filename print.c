/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:48:16 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/24 19:32:59 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "init/shell_parse_init.h"
#include "shell/shell.h"
#include "parse/shell_parse.h"
#include "utils/state_machine_utils_01.h"

int count = 0;

void	print_recur(t_shell_tree_node *t, int left)
{
	char	*which[] = {"root", "empty", "string", "int", "cmd", "|", "&&", "||", "<", ">", "<<", ">>"};
	int cnt = 0;
	if (t)
	{
		printf("%d: tree %s" , count++, which[t->kind]);
		if (t->kind == T_PIPE)
			printf("%d", t->pnum);
		printf(" %d\n", left);

		if (NULL == t->argv)
			printf("	no argv\n");
		else
			while (t->argv[cnt])
			{
				printf("	%d: %s\n", cnt, t->argv[cnt]);
				++cnt;
			}
		if (NULL == t->filepath)
			printf("	no filepath\n");
		else
			printf("	file: %s\n", t->filepath);
		print_recur(t->left, 1);
		print_recur(t->right, 0);
		printf("up\n\n");
	}
}

void	print_tree(t_shell_data *shell)
{
	t_shell_tree_node	*cur;

	cur = &shell->tree;
	print_recur(cur, 0);
	printf("\n");
	count = 0;
	//shell_parse_free(shell);
	//shell->pipe_count = 0;
	//shell_parse_init(shell);
	//ft_set_status(shell, S_LINE_READ);
}
