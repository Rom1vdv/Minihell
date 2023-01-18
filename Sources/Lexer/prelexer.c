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

static int	parse_error(char *str, char c)
{
	write(2, "parse error : ", 14);
	if (str)
		write(2, str, ft_strlen(str));
	else
		write(2, &c, 1);
	write(2, "\n", 1);
	return (1);
}

static int	check_quotes(char *str)
{
	int		index;
	char	quote;
	char	paranthesis;
	char	pipe;
	int		redir;

	paranthesis = 0;
	pipe = -1;
	redir = 0;
	index = -1;
	while (str[++index])
	{
		// printf("str at %d : %c\n", index, str[index]);
		if (str[index] == '|')
		{
			if (pipe)
				return (parse_error("'|'", 0));
			pipe = 1;
		}
		else if (!ft_strchr("| '\"", str[index]))
			pipe = 0;
		if (ft_strchr("><", str[index]))
		{
			if (redir && (((redir > 0) && (str[index] == '<')) || (index > 0 && str[index - 1] == ' ')))
				return (parse_error(0, str[index]));
			redir += (str[index] == '>') - (str[index] == '<');
			if (redir * (1 - 2 * (redir < 0)) > 2)
				return (parse_error(0, str[index]));
		}
		else if (!ft_strchr("<> '\"", str[index]))
			redir = 0;
		if (ft_strchr("'\"", str[index]))
		{
			quote = str[index++];
			pipe = 0;
			redir = 0;
			while (str[index] && str[index] != quote)
				++index;
			if (!str[index])
				return (parse_error("quotes", 0));
		}
		else if (str[index] == ';')
			return (parse_error("';'", 0));
		paranthesis += (str[index] == '(') - (str[index] == ')');
	}
	if (paranthesis)
		return (parse_error("paranthesis", 0));
	if (pipe)
		return (parse_error("'|'", 0));
	if (redir)
		return (parse_error(0, "<>"[redir > 0]));
	return (0);
}

static int	only_cat(char *str)
{
	int	index;

	index = 0;
	while (str[index] == ' ')
		++index;
	if (!ft_strncmp(&str[index], "cat", 3))
	{
		index += 3;
		while (str[index] == ' ')
			++index;
		return (!str[index]);
	}
	return (0);
}

void	exec_pipe(char *block, t_ms *ms, int piping)
{
	int	pid;

	if (piping)
	{
		if (only_cat(block))
			return ;
		ft_pipe(ms->pipeout);
	}
	// printf("cmd = %s\n", block);
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
	pipe_section = ft_split_quotes(rl, '|'); // cat | cat | ls, what do we do ?
	if (ft_arraylen(pipe_section) > 1)
	{
		index = 0;
		ft_set_pipe(ms->pipein, -1, -1);
		ft_set_pipe(ms->pipeout, -1, -1);
		while (pipe_section[index])
		{
			// printf("working with %s\n", pipe_section[index]);
			ft_handle_redirs(pipe_section[index], ms, 1, pipe_section[index + 1] != 0);
			// exec_pipe(pipe_section[index], ms, pipe_section[index + 1] != 0);
			++index;
		}
	}
	else
	{
		ft_set_pipe(ms->pipein, -1, -1);
		ft_set_pipe(ms->pipeout, -1, -1);
		ft_handle_redirs(rl, ms, 0, 0);
	}
	ft_free_arr(pipe_section);
}
