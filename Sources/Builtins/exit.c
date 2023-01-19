/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:24:48 by romvan-d          #+#    #+#             */
/*   Updated: 2023/01/19 08:57:17 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static int	check_exit_args(char *lex)
{
	int	index;
	int	sign;
	
	sign = 0;
	index = 0;
	while (lex[index] == '-' || lex[index] == '+')
	{
		++sign;
		++index;
	}
	while (lex[index])
	{
		if (lex[index] < '0' || lex[index] > '9')
			return (1);
		++index;
	}
	return (sign > 1);
}

void	exec_exit(char **lex, t_ms *ms, char *rl, int piping)
{
	int	index;

	index = 1;
	while (lex[index])
	{
		if (index == 1)
		{
			if (check_exit_args(lex[index]))
				g_ret_cmd = 255;
			else
				g_ret_cmd = ft_atoi(lex[index]);
		}
		++index;
	}
	if (g_ret_cmd == 255)
		close_program(ms, rl, lex, piping);
	if (index > 2)
	{
		write(2, "exit: too many arguments\n", 26);
		g_ret_cmd = 1;
	}
	else
		close_program(ms, rl, lex, piping);
}