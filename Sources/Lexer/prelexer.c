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
	int		semicolon;

	paranthesis = 0;
	pipe = -1;
	redir = 0;
	semicolon = 0;
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
		if (str[index] == ';')
		{
			if (!semicolon)
				return (parse_error("';'", 0));
			semicolon = 0;
		}
		else if (str[index] != ' ')
			semicolon = 1;
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

// static int	only_cat(char *str)
// {
// 	int	index;

// 	index = 0;
// 	while (str[index] == ' ')
// 		++index;
// 	if (!ft_strncmp(&str[index], "cat", 3))
// 	{
// 		index += 3;
// 		while (str[index] == ' ')
// 			++index;
// 		return (!str[index]);
// 	}
// 	return (0);
// }

static void	ft_addpid(t_ms *ms)
{
	t_pid	*tmp;

	tmp = ft_malloc(sizeof(*tmp), "addpid");
	tmp->next = 0;
	if (!ms->last_pid)
	{
		ms->pids = tmp;
		ms->last_pid = tmp;
	}
	else
	{
		ms->last_pid->next = tmp;
		ms->last_pid = ms->last_pid->next;
	}
}

static void	ft_wait_pids(t_ms *ms)
{
	t_pid	*tmp;

		// printf("debug\n");
	while (ms->pids)
	{
		// printf("wait\n");
		tmp = ms->pids;
		ms->pids = ms->pids->next;
		ft_wait_child(tmp->value);
		free(tmp);
	}
	ms->pids = 0;
	ms->last_pid = 0;
}

void	exec_pipe(char *block, t_ms *ms, int piping)
{
	if (piping)
	{
		// if (only_cat(block))
		// 	return ;
		ft_pipe(ms->pipeout);
	}
	ft_addpid(ms);
	// printf("cmd = %s\n", block);
	// printf("pipein : [%d, %d], pipeout : [%d, %d]\n", ms->pipein[0], ms->pipein[1], ms->pipeout[0], ms->pipeout[1]);
	// printf("is %d open ? %d\n", ms->pipein[0], fcntl(ms->pipein[0], F_GETFD) != -1);
	// printf("is %d open ? %d\n", ms->pipeout[1], fcntl(ms->pipeout[1], F_GETFD) != -1);
	ft_fork(&ms->last_pid->value);
	if (!ms->last_pid->value)
	{
		ft_dup2(ms->pipein, 0);
		ft_close_pipe(ms->pipein);
		ft_dup2(ms->pipeout, 1);
		ft_close_pipe(ms->pipeout);
		lexer(block, ms, 1);
		exit(g_ret_cmd);
	}
	if (ms->pipeout[0] != -1 || ms->pipeout[1] == -1 || (ms->pipeout[1] != -1 && !piping))
	{
		// printf("DONTCOMEHERE\n");
		ft_close_pipe(ms->pipein);
		ft_set_pipe(ms->pipein, ms->pipeout[0], ms->pipeout[1]);
	}
	else //uncomment this after debug
		ft_close_pipe(ms->pipeout);
	ft_set_pipe(ms->pipeout, -1, -1);
	// ft_wait_child(pid);
	// printf("AFTERpipein : [%d, %d], pipeout : [%d, %d]\n", ms->pipein[0], ms->pipein[1], ms->pipeout[0], ms->pipeout[1]);
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
	int		semicolons_index;
	char	**pipe_section;
	char	**semicolons;

	if (!rl[0])
		return ;
	if (check_quotes(rl))
	{
		g_ret_cmd = 258;
		return ;
	}
	semicolons_index = 0;
	semicolons = ft_split_quotes(rl, ';');
	while (semicolons[semicolons_index])
	{
		ft_set_pipe(ms->pipein, -1, -1);
		ft_set_pipe(ms->pipeout, -1, -1);
		pipe_section = ft_split_quotes(semicolons[semicolons_index], '|'); // cat | cat | ls, what do we do ?
		if (ft_arraylen(pipe_section) > 1)
		{
			index = 0;
			while (pipe_section[index])
			{
				// printf("working with %s\n", pipe_section[index]);
				ft_handle_redirs(pipe_section[index], ms, 1, pipe_section[index + 1] != 0);
				// exec_pipe(pipe_section[index], ms, pipe_section[index + 1] != 0);
				++index;
			}
		}
		else
			ft_handle_redirs(semicolons[semicolons_index], ms, 0, 0);
		ft_close_pipe(ms->pipein);
		ft_close_pipe(ms->pipeout);
		ft_free_arr(pipe_section);
		free(ms->file_name);
		ft_wait_pids(ms);
		++semicolons_index;
	}
	ft_free_arr(semicolons);
}
