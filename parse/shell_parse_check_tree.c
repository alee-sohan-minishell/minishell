#include "../shell/shell.h"

int	shell_parse_check_tree(t_shell_tree_node *focus)
{
	// TODO 순회하면서 다음 상황 만나면 에러
	/*
	// open
	else if ('&' == c || '|' == c)
		return (S_P_ERROR);

	// pipe
	else if (')' == c || '&' == c)
		return (S_P_ERROR);
	*/
	return (0);
}

// TODO 언젠가 tree 구조로 parse error 출력하는 거 만들었으면 좋겠다.
