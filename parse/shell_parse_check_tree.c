/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_check_tree.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:11:20 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/29 20:29:55 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "../utils/error_msg_utils_01.h"
#include "../parse/shell_parse_util_tree.h"
#include "../parse/shell_parse_state.h"
#include "../parse/shell_parse_util_node_list.h"
#include "../parse/shell_parse_util_tree2.h"

int	shell_parse_check_tree(t_shell_tree_node *t)
{
	if (T_PIPE == t->kind
		&& (NULL == t->left || T_BOOL_AND == t->left->kind
			|| NULL == t->right || T_BOOL_AND == t->right->kind))
	{
		ft_self_perror_param("parse", "|", "has no child");
		return (-1);
	}
	else if (is_redirect(t->kind) && NULL == t->filepath)
	{
		ft_self_perror_param("parse", "redirect", "has no filepath");
		return (-1);
	}
	if (t->left)
		if (shell_parse_check_tree(t->left))
			return (-1);
	if (t->right)
		if (shell_parse_check_tree(t->right))
			return (-1);
	return (0);
}

t_state_shell_parse	return_redirect_env(t_shell_data *p_data, char c)
{
	if ('\'' == c)
		return (S_P_REDIRECT_QUOTE);
	else if ('"' == c)
		return (S_P_REDIRECT_DQUOTE);
	else if ('$' == c)
		return (S_P_REDIRECT_ENV);
	if (shell_parse_node_add_char(p_data->parse_tmp, c))
		return (S_P_ERROR);
	return (get_redirect_state(p_data->redirect_kind));
}
