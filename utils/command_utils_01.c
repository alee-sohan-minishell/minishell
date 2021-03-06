/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils_01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 03:39:32 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 03:40:51 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	get_cmd_count(char **cmd)
{
	int	idx;

	if (!cmd)
		return (0);
	idx = 0;
	while (cmd[idx])
		idx++;
	return (idx);
}
