/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:39:34 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 16:21:31 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXPORT_UTILS_H
# define FT_EXPORT_UTILS_H
# include "../env/env_list.h"

int		malloc_export_buffer(char ***buf, t_env_list *p_list, int *buf_len);
int		free_export_buffer(char ***buf, int idx);
void	sort_export_buffer(char ***buf, int buf_max);
void	export_string_cat(char *p_value, char **buf, int buf_idx, int buf_len);
int		export_str_len(char *p_value);

#endif
