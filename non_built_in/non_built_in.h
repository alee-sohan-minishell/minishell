/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_built_in.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan<sohan@student.42seoul.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 08:49:12 by sohan             #+#    #+#             */
/*   Updated: 2022/06/29 18:26:52 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NON_BUILT_IN_H
# define NON_BUILT_IN_H

# include "../shell/shell.h"

void	ft_non_built_in(t_shell_data *p_data);
void	search_execute(t_shell_data *p_data, char **path_list);
void	direct_execute(t_shell_data *p_data);

#endif
