/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse_util_tree2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 21:53:31 by min-jo            #+#    #+#             */
/*   Updated: 2022/06/25 23:31:50 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "shell_parse_state.h"
#include "../tree_heredoc/shell_tree.h"
#include "../tree_heredoc/shell_heredoc.h"
#include "../libft/libft.h"

t_state_shell_parse	get_redirect_state(t_shell_tree_kind kind)
{
	if (T_REDIRECT_IN == kind)
		return (S_P_REDIRECT_IN);
	else if (T_REDIRECT_OUT == kind)
		return (S_P_REDIRECT_OUT);
	else if (T_REDIRECT_HEREDOC == kind)
		return (S_P_REDIRECT_HEREDOC);
	else if (T_REDIRECT_APPEND == kind)
		return (S_P_REDIRECT_APPEND);
	return (S_P_ERROR);
}

int	insert_heredoc_node(t_shell_data *p_data, char *str)
{
	t_shell_heredoc_node	*node;

	node = heredoc_new_node(str);
	if (NULL == node)
		return (-1);
	heredoc_list_add(&p_data->heredoc_list, node);
	return (0);
}

char	*make_heredoc_filename(int *cnt)
{
	char	*num;
	char	*joined;

	num = ft_itoa(*cnt);
	if (NULL == num)
		return (NULL);
	joined = ft_strjoin("filename", num); // TODO filename이랑 path 뭐로 할지 정해야 함
	if (NULL == joined)
		return (NULL);
	++(*cnt);
	return (joined);
}
