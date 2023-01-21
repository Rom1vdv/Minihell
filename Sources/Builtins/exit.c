/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:24:48 by romvan-d          #+#    #+#             */
/*   Updated: 2023/01/21 20:23:10 by marvin           ###   ########.fr       */
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
	if (lex[1])
	{
		if (check_exit_args(lex[1]))
			g_ret_cmd = 255;
		else
			g_ret_cmd = ft_atoi_64bits(lex[1]);
	}
	if (g_ret_cmd >= 255 && lex[1])
	{
		g_ret_cmd = 255;
		ft_stderr("-minishell: exit: ", lex[1], NUM_ERR);
		close_program(ms, rl, lex, piping);
	}
	if (lex[1] && lex[2])
	{
		write(2, "-minishell: exit: too many arguments\n", 37);
		g_ret_cmd = 1;
	}
	else
		close_program(ms, rl, lex, piping);
}
