/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 02:50:54 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 05:33:44 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXPORT_H
# define FT_EXPORT_H

int		ft_export(char **cmd, t_env_list *p_list);
void	print_export(t_env_list *p_list);
int		malloc_export_buffer(char ***buf, t_env_list *p_list, int *buf_len);
int		free_export_buffer(char ***buf, int idx);
void	copy_export_buffer(char ***buf, t_env_list *p_list);

#endif
