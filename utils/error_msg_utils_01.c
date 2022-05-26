/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg_utils_01.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 03:04:07 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 18:35:52 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <string.h>
#include <errno.h>
#include "../shell/shell.h"
#include "error_msg_utils_01.h"

void	ft_perror(const char *msg)
{
	char	*buf;
	int		buf_len;
	char	*err_msg;

	buf_len = 0;
	if (msg)
		buf_len += ft_strlen(msg) + ft_strlen(" :");
	err_msg = strerror(errno);
	if (err_msg)
		buf_len += ft_strlen(err_msg);
	buf = (char *)malloc(++buf_len);
	if (!buf)
		return (ft_msg_exit("ft_perror malloc failed", 255, STDERR_FILENO));
	buf[0] = '\0';
	if (msg)
	{
		ft_strlcat(buf, msg, buf_len);
		ft_strlcat(buf, ": ", buf_len);
	}
	if (err_msg)
		ft_strlcat(buf, err_msg, buf_len);
	ft_putendl_fd(buf, STDERR_FILENO);
	free(buf);
	return ;
}

void	ft_perror_param(const char *pre_cmd, const char *param, int errno_flag)
{
	int		len;
	char	*err_msg;
	char	*buf;

	len = ft_perror_param_len(pre_cmd, param);
	if (errno_flag)
	{
		err_msg = strerror(errno);
		len += ft_strlen(err_msg);
	}
	buf = (char *)malloc(++len);
	if (!buf)
		return (ft_msg_exit("ft_perror_param malloc failed", \
		255, STDERR_FILENO));
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
	if (errno_flag)
		ft_strlcat(buf, err_msg, len);
	ft_putendl_fd(buf, STDERR_FILENO);
	free(buf);
}

void	ft_self_perror_param(const char *pre_cmd, \
					const char *param, const char *err_msg)
{
	int		len;
	char	*buf;

	len = ft_perror_param_len(pre_cmd, param);
	if (err_msg)
		len += ft_strlen(err_msg);
	buf = (char *)malloc(++len);
	if (!buf)
		return (ft_msg_exit("ft_custom_error_param malloc failed", \
		255, STDERR_FILENO));
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
	if (err_msg)
		ft_strlcat(buf, err_msg, len);
	ft_putendl_fd(buf, STDERR_FILENO);
	free(buf);
}

void	ft_perror_exit(const char *msg, int exit_status)
{
	ft_perror(msg);
	exit(exit_status);
}

int	ft_msg_return(const char *msg, int return_value, int std_type)
{
	ft_putendl_fd(msg, std_type);
	return (return_value);
}

void	ft_msg_exit(const char *msg, int exit_status, int std_type)
{
	ft_putendl_fd(msg, std_type);
	exit(exit_status);
	return ;
}

int	ft_perror_param_len(const char *pre_cmd, const char *param)
{
	int		ret;

	ret = 0;
	ret += ft_strlen(STR_SHELL) + ft_strlen(": ");
	if (pre_cmd)
		ret += ft_strlen(pre_cmd) + ft_strlen(": ");
	if (param)
		ret += ft_strlen(param) + ft_strlen(": ");
	return (ret);
}
