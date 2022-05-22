/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:57:11 by alee              #+#    #+#             */
/*   Updated: 2022/05/22 12:41:59 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "../utils/utils_01.h"
#include "../libft/libft.h"
#include "ft_cd.h"
#include "../shell/shell.h"

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
			ft_cd_perror("cd", cmd[1]);
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

void	ft_cd_perror(const char *pre_cmd, char *param)
{
	char	*err_msg;
	char	*buf;
	int		len;

	err_msg = strerror(errno);
	len = ft_strlen(STR_SHELL) + ft_strlen(": ") + ft_strlen(pre_cmd) + \
	ft_strlen(": ") + ft_strlen(param) + ft_strlen(": ") + ft_strlen(err_msg);
	buf = malloc((sizeof(char) * len) + 1);
	if (!buf)
		ft_msg_exit("ft_cd_perror failed", 255, STDERR_FILENO);
	buf[0] = '\0';
	ft_strlcat(buf, STR_SHELL, len);
	ft_strlcat(buf, ": ", len);
	if (pre_cmd)
	{
		ft_strlcat(buf, pre_cmd, len);
		ft_strlcat(buf, ": ", len);
	}
	if (param)
	{
		ft_strlcat(buf, param, len);
		ft_strlcat(buf, ": ", len);
	}
	ft_strlcat(buf, err_msg, len);
	ft_putendl_fd(buf, STDERR_FILENO);
	free(buf);
	return ;
}
