/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan<sohan@student.42seoul.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 01:58:06 by sohan             #+#    #+#             */
/*   Updated: 2022/06/29 18:26:33 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <unistd.h>
#include "../shell/shell.h"

void	display_logo(t_shell_data *s_data)
{
	ft_putstr_fd("███╗   ███╗██╗███╗   ██╗██╗    ", STDOUT_FILENO);
	ft_putstr_fd("██╗  ██╗███████╗██╗     ██╗\n", STDOUT_FILENO);
	ft_putstr_fd("████╗ ████║██║████╗  ██║██║    ", STDOUT_FILENO);
	ft_putstr_fd("██║  ██║██╔════╝██║     ██║\n", STDOUT_FILENO);
	ft_putstr_fd("██╔████╔██║██║██╔██╗ ██║██║    ", STDOUT_FILENO);
	ft_putstr_fd("███████║█████╗  ██║     ██║\n", STDOUT_FILENO);
	ft_putstr_fd("██║╚██╔╝██║██║██║╚██╗██║██║    ", STDOUT_FILENO);
	ft_putstr_fd("██╔══██║██╔══╝  ██║     ██║\n", STDOUT_FILENO);
	ft_putstr_fd("██║ ╚═╝ ██║██║██║ ╚████║██║    ", STDOUT_FILENO);
	ft_putstr_fd("██║  ██║███████╗███████╗███████╗\n", STDOUT_FILENO);
	ft_putstr_fd("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝    ╚═╝", STDOUT_FILENO);
	ft_putstr_fd("  ╚═╝╚══════╝╚══════╝╚══════╝\n", STDOUT_FILENO);
	ft_putstr_fd("\t\t\t\t\t        sohan& min-jo\n", STDOUT_FILENO);
	s_data->status = S_INIT;
	return ;
}
