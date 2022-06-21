/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 14:06:10 by alee              #+#    #+#             */
/*   Updated: 2022/06/21 14:11:07 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "error_msg_utils_01.h"

int	ft_pipe(int	fildes[2])
{
	int	result;

	result = pipe(fildes);
	if (result)
		ft_msg_exit("pipe Failed \n", 1, STDERR_FILENO);
	return (result);
}
