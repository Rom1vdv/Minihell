/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:36:28 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/13 18:22:32 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static int	check_quotes(char *str)
{
	int		index;
	char	quote;

	index = 0;
	while (str[index])
	{
		if (ft_strchr("'\"", str[index]))
		{
			quote = str[index++];
			while (str[index] && str[index] != quote)
				++index;
			if (!str[index])
			{
				printf("Unclosed quotes detected, pls fix\n");
				return (1);
			}
		}
		// else if (ft_strchr("&|", str[index]) && handle_andor(str, &index, str[index]))
		// {
		// 	printf("parse error near'%c'\n", str[index]);
		// 	return (1);
		// }
		++index;
	}
	return (0);
}

/* implementing && and || bonuses                            *
*  cmd && cmd2 -> cmd2 is exec only if exit code of cmd == 0 *
*  cmd || cmd2 -> cmd2 is exec only if exit code of cmd != 0 *
*  cmd & cmd2  -> ???                                        *
*  cmd | cmd2  -> just a pipe, do nothing here               *
*  cmd &&& cmd2 -> parse error near `&'                      *
*  cmd ||| cmd2 -> parse error near `|'                      *
*  cmd & & cmd2 -> parse error near '&'                      *
*  cmd | | cmd2 -> parse error near '|'                      */
void	lexer_bonus(char *rl, t_ms *ms)
{
	if (!rl[0])
		return ;
	if (check_quotes(rl))
	{
		ms->ret_cmd = 1;
		return ;
	}
	lexer(rl, ms);
}
