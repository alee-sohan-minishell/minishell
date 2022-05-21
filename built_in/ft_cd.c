/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:57:11 by alee              #+#    #+#             */
/*   Updated: 2022/05/21 14:06:09 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../utils/utils_01.h"
#include "../libft/libft.h"
#include "ft_cd.h"

int	ft_cd(char **cmd)
{
	int	ret;

	if (!cmd || !(*cmd))
		return (1);
	if (cmd[0])
	{
		if (is_chdir_home(cmd) == 1)
			ret = chdir("/Users/alee");
		else
			ret = chdir(cmd[1]);
		if (ret == -1)
		{
			ft_perror("cd");
			return (1);
		}
	}
	return (0);
}

int	is_chdir_home(char **cmd)
{
	if (cmd[1] == NULL)
		return (1);
	if (ft_strcmp(cmd[1], "~") == 0 || ft_strcmp(cmd[1], "#") == 0)
		return (1);
	return (0);
}
