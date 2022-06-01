#include "../shell/shell.h"
#include "../libft/libft.h"
#include "../utils/state_machine_utils_01.h"
#include "../built_in/ft_cd.h"
#include "../built_in/ft_pwd.h"
#include "../built_in/ft_echo.h"
#include "../built_in/ft_exit.h"
#include "../built_in/ft_env.h"
#include "../built_in/ft_unset.h"
#include "../built_in/ft_export.h"
#include "../non_built_in/non_built_in.h"
#include "../init/shell_utils_01.h"
#include "../redirection/redirection.h"
#include "../excute/shell_excute.h"

void	set_fd(t_shell_data *p_data, const char *filename, int type)
{
	if (type == T_REDIRECT_IN)
		redirection_in(p_data, filename);
	else if (type == T_REDIRECT_OUT)
		redirection_out(p_data, filename);
	else if (type == T_REDIRECT_APPEND)
		redirection_append(p_data, filename);
}

void	tree_traverse(t_shell_tree_node *cmd_tree)
{
	if (cmd_tree)
	{
		/*do something here
		 *
		 */
		tree_traverse(cmd_tree->left);
		tree_traverse(cmd_tree->right);
	}
}

void	shell_execute_tree(t_shell_data *p_data)
{
	if (!p_data)
		return ;
	p_data->fd_out_old = dup(STDOUT_FILENO);
	p_data->fd_in_old = dup(STDIN_FILENO);
	p_data->fd_out_new = dup(STDOUT_FILENO);
	p_data->fd_in_new = dup(STDIN_FILENO);
	tree_traverse(p_data->cmd_tree);
	if (p_data->line)
		free(p_data->line);
	ft_set_status(p_data, S_LINE_READ);
	dup2(p_data->fd_out_old, STDOUT_FILENO);
	dup2(p_data->fd_in_old, STDIN_FILENO);
	close(p_data->fd_out_old);
	close(p_data->fd_in_old);
	return ;
}
