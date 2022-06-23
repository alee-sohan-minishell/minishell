/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alee <alee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:08:02 by alee              #+#    #+#             */
/*   Updated: 2022/05/26 13:16:45 by alee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell/shell.h"
#include "../utils/state_machine_utils_01.h"
#include "../libft/libft.h"
#include "shell_parse.h"

/****************temp implementation**********/
#include "../env/env_list_interface_01.h"

int	is_seperator(char *charset, char c)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

int		cmd_count(const char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (*str)
	{
		while (str[i] && !is_seperator("|<>", str[i]))
			++i;
		str += i;
		if (is_seperator("|<>", *str))
			++str;
		if (is_seperator("|<>", *str))
			++str;
		i = 0;
		++count;
	}
	return (count);
}

/****************** to here********************/


int	is_stack_empty(t_stack *stack)
{
	if (stack->size >= MAX_LINE_LEN - 1)
		return (1);
	return (0);
}

int	is_stack_full(t_stack *stack)
{
	if (stack->size < 0)
		return (1);
	return (0);
}

void	push(t_stack *stack, int val)
{
	if (!is_stack_full(stack))
		stack->arr[++stack->size] = val;
}

int		pop(t_stack *stack)
{
	if (!is_stack_empty(stack))
		return (stack->arr[stack->size--]);
	return (-1);
}

int	is_qoute_unclosed(char *str)
{
	int		dqoute;
	int		qoute;
	
	dqoute = 0;
	qoute = 0;
	while (*str)
	{
		if (*str == '\'')
			++qoute;
		else if (*str == '\"')
			++dqoute;
		++str;
	}
	if ((qoute % 2) || (dqoute % 2))
		return (1);
	return (0);
}

int	is_metacharacter(char c)
{
	if (c == ' ' || )
}

void	get_token_list(t_token_list *list, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		
	}
}

void	shell_parse(t_shell_data *p_data)
{
	t_token_list	token_list;

	token_list.head = NULL;
	token_list.tail = NULL;
	token_list.size = 0;

	if (!p_data)
		return ;
	if (is_qoute_unclosed(p_data->line))
	{	
		write(2, "unclosed qoute\n", 15);
		ft_set_status(p_data, S_ERROR);
		return ;
	}
	p_data->cmd_count = cmd_count(p_data->line);
	if (!p_data->cmd_count)
	{
		ft_set_status(p_data, S_LINE_READ);
		free(p_data->line);
		return ;
	}
	p_data->cmd_graph = cmd_split(p_data->line, "|<>", p_data->cmd_count);
	//printf("count:%d\n", p_data->cmd_count);
	//display_graph(p_data->cmd_graph);
	/*p_data->cmd = ft_split(p_data->line, ' ');
	if (!p_data->cmd)
	{
		ft_set_status(p_data, S_ERROR);
		return ;
	}*/
	ft_set_status(p_data, S_CMD);
	return ;
}
