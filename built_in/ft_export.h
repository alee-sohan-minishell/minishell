/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 02:50:54 by alee              #+#    #+#             */
/*   Updated: 2022/05/25 15:40:34 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXPORT_H
# define FT_EXPORT_H

int		ft_export(char **cmd, t_env_list *p_list);
void	print_export(t_env_list *p_list);
void	print_export_buffer(char ***buf, int buf_max);
int		add_export(char **buf, t_env_list *p_list);
int		extract_key_value(char *line, char **o_key, char **o_value);

#endif
