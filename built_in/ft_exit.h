/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 02:46:50 by alee              #+#    #+#             */
/*   Updated: 2022/05/21 08:42:12 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXIT_H
# define FT_EXIT_H

int	ft_exit(char **cmd, long long status);
int	get_cmd_count(char **cmd);
int	is_valid_num(char *str);
int	ft_atol(char *str, long long *o_var);

#endif
