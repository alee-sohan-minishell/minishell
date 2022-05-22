/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 04:41:18 by alee              #+#    #+#             */
/*   Updated: 2022/05/22 13:14:27 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell/shell.h"
#include "libft/libft.h"
#include "logo/logo.h"
#include "init/shell_init.h"
#include "read_line/shell_readline.h"

//debug
#include "env/env_list.h"
#include <stdio.h>

int	main(int argc, char *argv[], char *env[])
{
	//
		if (argc == (int)argv == (int)env)
			return (1);

	//

	t_env_list	list;

	env_list_init(&list);
	printf("%d \n", list.node_count);
	printf("head : %p \n", &list.dummy_head);
	printf("tail : %p \n", &list.dummy_tail);

	printf("head.prev : %p \n", &list.dummy_head.prev);
	printf("head.next : %p \n", &list.dummy_head.next);
	printf("tail.prev : %p \n", &list.dummy_tail.prev);
	printf("tail.Next : %p \n", &list.dummy_tail.next);


	// t_shell_data	shell;

	// ft_bzero(&shell, sizeof(shell));
	// while (1)
	// {
	// 	if (shell.status == S_START)
	// 		display_logo(&shell);
	// 	else if (shell.status == S_INIT)
	// 		shell_init(&shell, argc, &argv, &env);
	// 	else if (shell.status == S_LINE_READ)
	// 		shell_readline(&shell);
	// 	// else if (shell.status == S_PARSE)
	// 	// 	shell_parse(...);
	// 	// else if (shell.status == S_CMD)
	// 	// 	shell_excute(...);
	// 	else if (shell.status == S_CLOSE || shell.status == S_ERROR)
	// 		break ;
	// }
	// return (shell.last_status);
}
