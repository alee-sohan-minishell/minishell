/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 04:41:18 by alee              #+#    #+#             */
/*   Updated: 2022/06/21 23:34:23 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell/shell.h"
#include "libft/libft.h"
#include "logo/logo.h"
#include "init/shell_init.h"
#include "read_line/shell_readline.h"
#include "utils/state_machine_utils_01.h"
#include "parse/shell_parse.h"
#include "excute/shell_excute.h"

// TODO
#include <stdlib.h>
#include "init/shell_parse_init.h"

int count = 0;

void	print_recur(t_shell_tree_node *t, int left)
{
	char	*which[] = {"root", "empty", "string", "int", "cmd", "|", "&&", "||", "<", ">", "<<", ">>"};
	int cnt = 0;

	printf("%d: tree %s %d\n", count++, which[t->kind], left);

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

	if (t->left)
		print_recur(t->left, 1);
	if (t->right)
		print_recur(t->right, 0);
	printf("up\n\n");
}

void	print_tree(t_shell_data *shell)
{
	print_recur(shell->tree.right, 0);
	printf("\n");
	count = 0;
	shell_parse_free(shell);
	shell_parse_init(shell);
	ft_set_status(shell, S_LINE_READ);
}

int	main(int argc, char *argv[], char *env[])
{
	t_shell_data	shell;

	ft_bzero(&shell, sizeof(shell));
	while (1)
	{
		if (shell.status == S_START)
			display_logo(&shell);
		else if (shell.status == S_INIT)
			shell_init(&shell, argc, &argv, &env);
		else if (shell.status == S_LINE_READ)
			shell_readline(&shell);
		else if (shell.status == S_PARSE)
			shell_parse(&shell);
		// TODO
		else if (shell.status == S_CMD)
			shell_execute_tree(&shell);
		else if (shell.status == S_CLOSE || shell.status == S_ERROR)
			break ;
	}
	status_close(&shell);
	// while (1); // TODO
	return (shell.last_status);
}
