/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 04:41:18 by alee              #+#    #+#             */
/*   Updated: 2022/06/25 23:35:08 by min-jo           ###   ########.fr       */
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
#include "print.h"

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
		else if (shell.status == S_CMD)
		{
			print_heredoc(&shell); // TODO
			print_tree(&shell); // TODO
			// TODO: herdoc list 순회하면서 사용자 입력 받아서, file에 저장해놔야 함, heredoc_list에 delimiter eof로 사용하면 됨
			// 파싱에서 트리 만들 때 filename 넣어주게 고침
			// 파일 만들 때 filename_1 filename_2 처럼 heredoc list 순회하는 순서가 파일 이름에 있어야, tree node에서 그걸 참조할 수 있음
			shell.heredoc_cnt = 0; // make_heredoc_filename() 함수를 그대로 사용할거면 heredoc_cnt 초기화 하고 써야 됨, 호출한 순서대로 파일이름 메겨지니까
			shell_execute_tree(&shell);
		}
		else if (shell.status == S_CLOSE || shell.status == S_ERROR)
			break ;
	}
	status_close(&shell);
	return (shell.last_status);
}
