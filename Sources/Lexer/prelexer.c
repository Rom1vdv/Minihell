/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prelexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:40:29 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/17 10:40:29 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static int	parse_error(char *str)
{
	write(2, "parse error : ", 14);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
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
			pipe = 0;
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
		return (parse_error("'|'"));
	return (0);
}

static void	exec_block(char *block, t_ms *ms, int piping)
{
	int	pid;

	if (piping)
		ft_pipe(ms->pipeout);
	// printf("pipein : [%d, %d], pipeout : [%d, %d]\n", ms->pipein[0], ms->pipein[1], ms->pipeout[0], ms->pipeout[1]);
	ft_fork(&pid);
	if (!pid)
	{
		ft_dup2(ms->pipein, 0);
		ft_close_pipe(ms->pipein);
		ft_dup2(ms->pipeout, 1);
		ft_close_pipe(ms->pipeout);
		lexer(block, ms, 1);
		exit(ms->ret_cmd);
	}
	ft_close_pipe(ms->pipein);
	ft_set_pipe(ms->pipein, ms->pipeout[0], ms->pipeout[1]);
	ft_set_pipe(ms->pipeout, -1, -1);
	ft_wait_child(pid, &ms->ret_cmd);
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
		ft_set_pipe(ms->pipein, -1, -1);
		ft_set_pipe(ms->pipeout, -1, -1);
		while (pipe_section[index])
		{
			exec_block(pipe_section[index], ms, pipe_section[index + 1] != 0);
			++index;
		}
		ft_free_arr(pipe_section);
	}
	else
		lexer(rl, ms, 0);
}