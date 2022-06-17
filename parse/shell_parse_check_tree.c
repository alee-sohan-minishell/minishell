#include "../shell/shell.h"

int	shell_parse_check_tree(t_shell_data *p_data)
{
	// TODO 순회하면서 다음 상황 만나면 에러

	// open
	else if ('&' == c || '|' == c)
		return (S_P_ERROR);

	// pipe
	else if (')' == c || '&' == c)
		return (S_P_ERROR);
}

void	shell_parse_print_check_tree(t_shell_data *p_data)
{
	// TODO
	ft_perror_param("parse", str, 0);
}
