/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_01.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 03:50:11 by alee              #+#    #+#             */
/*   Updated: 2022/06/23 21:38:11 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_UTILS_01_H
# define STRING_UTILS_01_H

int		is_variable_rule(char ch);
void	ft_strcat_buf(char *buf, int buf_len, const char *pre_cmd, \
					const char *param);

#endif
