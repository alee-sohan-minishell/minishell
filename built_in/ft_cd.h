/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:56:59 by alee              #+#    #+#             */
/*   Updated: 2022/05/22 17:56:53 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CD_H
# define FT_CD_H

int		ft_cd(char **cmd);
int		is_chdir_home(char **cmd);
void	cd_perror(const char *pre_cmd, char *param);

#endif
