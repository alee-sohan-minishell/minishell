/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg_utils_02.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:15:56 by alee              #+#    #+#             */
/*   Updated: 2022/06/23 21:40:39 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../shell/shell.h"
#include "../utils/string_utils_01.h"

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

void	ft_self_perror_param_exit(const char *pre_cmd, \
					const char *param, const char *err_msg, int exit_status)
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
	ft_strcat_buf(buf, len, pre_cmd, param);
	if (err_msg)
		ft_strlcat(buf, err_msg, len);
	ft_putendl_fd(buf, STDERR_FILENO);
	free(buf);
	exit(exit_status);
}
