#include "../shell/shell.h"

int	shell_parse_check_tree(t_shell_tree_node *focus)
{
	// TODO 순회하면서 다음 상황 만나면 에러
	focus = NULL;
	(void)focus;
	return (0);
	/*
	// open
	else if ('&' == c || '|' == c)
		return (S_P_ERROR);

	// pipe
	// 파이프 밑에 자식 없는 경우 cat "fdsf" |    |<d
	else if (')' == c || '&' == c)
		return (S_P_ERROR);

	// heredoc이나 redirect 내용물에 파일 없는 경우
	*/
}

// TODO 언젠가 tree 구조로 parse error 출력하는 거 만들었으면 좋겠다.
