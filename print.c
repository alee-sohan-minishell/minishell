/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:48:16 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/28 19:07:45 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init/shell_parse_init.h"
#include "shell/shell.h"
#include "parse/shell_parse.h"
#include "utils/state_machine_utils_01.h"
#include "libft/libft.h"

static void	print_content(t_shell_tree_node *t)
{
	int			cnt;

	if (NULL == t->argv)
		ft_putstr_fd("	no argv\n", STDERR_FILENO);
	else
	{
		cnt = -1;
		while (t->argv[++cnt])
		{
			ft_putchar_fd('\t', STDERR_FILENO);
			ft_putnbr_fd(cnt, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(t->argv[cnt], STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
		}
	}
	ft_putchar_fd('\t', STDERR_FILENO);
	if (NULL == t->filepath)
		ft_putstr_fd("no filepath\n", STDERR_FILENO);
	else
	{
		ft_putstr_fd("file: ", STDERR_FILENO);
		ft_putstr_fd(t->filepath, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
}

void	print_recur(t_shell_tree_node *t, int left, int *count)
{
	const char	*which[] = {
		"root", "empty", "string", "int", "cmd",
		"|", "&&", "||", "<", ">", "<<", ">>"};

	ft_putnbr_fd((*count)++, STDERR_FILENO);
	ft_putstr_fd(": tree ", STDERR_FILENO);
	ft_putstr_fd(which[t->kind], STDERR_FILENO);
	if (t->kind == T_PIPE)
		ft_putnbr_fd(t->pnum, STDERR_FILENO);
	ft_putnbr_fd(left, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	print_content(t);
	if (t->left)
		print_recur(t->left, 1, count);
	if (t->right)
		print_recur(t->right, 0, count);
	ft_putstr_fd("up\n", STDERR_FILENO);
}

void	print_heredoc(t_shell_data *shell)
{
	t_shell_heredoc_node	*node;
	int						cnt;

	cnt = -1;
	node = shell->heredoc_list.head.next;
	while (node != &shell->heredoc_list.tail)
	{
		ft_putnbr_fd(++cnt, STDERR_FILENO);
		ft_putstr_fd(": heredoc, delimiter: ", STDERR_FILENO);
		ft_putstr_fd("node->delimiter", STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		node = node->next;
	}
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	print_tree(t_shell_data *shell)
{
	int	count;

	count = 0;
	print_recur(&shell->tree, 0, &count);
	ft_putchar_fd('\n', STDERR_FILENO);
}
