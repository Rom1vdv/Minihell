/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:36:28 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/14 16:04:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static int	parse_error(char *str)
{
	printf("parse error : %s\n", str);
	return (1);
}

static int	check_quotes(char *str)
{
	int		index;
	char	quote;
	char	paranthesis;

	paranthesis = 0;
	index = -1;
	while (str[++index])
	{
		if (ft_strchr("'\"", str[index]))
		{
			quote = str[index++];
			while (str[index] && str[index] != quote)
				++index;
			if (!str[index])
				return (parse_error("quotes"));
		}
		else if (str[index] == '(')
			++paranthesis;
		else if (str[index] == ')')
			--paranthesis;
	}
	if (paranthesis)
		return (parse_error("paranthesis"));
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
