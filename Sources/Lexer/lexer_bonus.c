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
	char	pipe;

	paranthesis = 0;
	pipe = -1;
	index = -1;
	while (str[++index])
	{
		if (str[index] == '|')
		{
			if (pipe)
				return (parse_error("'|'"));
			pipe = 1;
		}
		else if (!ft_strchr("| '\"", str[index]))
			pipe = 0;
		if (ft_strchr("'\"", str[index]))
		{
			quote = str[index++];
			while (str[index] && str[index] != quote)
				++index;
			if (!str[index])
				return (parse_error("quotes"));
		}
		else if (str[index] == ';')
			return (parse_error("';'"));
		paranthesis += (str[index] == '(') - (str[index] == ')');
	}
	if (paranthesis)
		return (parse_error("paranthesis"));
	if (pipe)
		return (parse_error("pipe"));
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
	int		index;
	char	**pipe_section;

	if (!rl[0])
		return ;
	if (check_quotes(rl))
	{
		ms->ret_cmd = 1;
		return ;
	}
	if (ft_strchr(rl, '|'))
	{
		pipe_section = ft_split(rl, '|');
		index = 0;
		while (pipe_section[index])
		{
			lexer(pipe_section[index], ms);
			++index;
		}
		ft_free_arr(pipe_section);
	}
	else
		lexer(rl, ms);
}
