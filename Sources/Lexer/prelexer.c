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

static void	exec_block(t_ms *ms, char *block)
{
	int		index;

	ft_set_pipe(ms->pipein, -1, -1);
	ft_set_pipe(ms->pipeout, -1, -1);
	ms->pipes = ft_split_quotes(block, '|');
	if (ft_arraylen(ms->pipes) > 1)
	{
		index = 0;
		while (ms->pipes[index] && !ms->error_fork)
		{
			ft_handle_redirs(ms->pipes[index], ms, 1,
				ms->pipes[index + 1] != 0);
			++index;
		}
	}
	else
		ft_handle_redirs(block, ms, 0, 0);
	ft_close_pipe(ms->pipein);
	ft_close_pipe(ms->pipeout);
	ft_free_arr(ms->pipes);
	ft_wait_pids(ms);
}

void	prelexer(char *rl, t_ms *ms)
{
	int		index;

	if (check_parse_error(rl))
	{
		g_ret_cmd = 258;
		return ;
	}
	index = 0;
	ms->error_fork = 0;
	ms->semicolons = ft_split_quotes(rl, ';');
	while (ms->semicolons[index] && !ms->error_fork)
	{
		exec_block(ms, ms->semicolons[index]);
		++index;
	}
	ft_free_arr(ms->semicolons);
	if (ms->error_fork)
		g_ret_cmd = 1;
}

	// printf("piping %d, cmd = %s\n", piping, block);
	// printf("pipein : [%d, %d], pipeout : [%d, %d]\n", ms->pipein[0],
	// 	ms->pipein[1], ms->pipeout[0], ms->pipeout[1]);
	// printf("is %d open ? %d\n", ms->pipein[0], fcntl(ms->pipein[0], 
	// 	F_GETFD) != -1);
	// printf("is %d open ? %d\n", ms->pipeout[1], fcntl(ms->pipeout[1], 
	// 	F_GETFD) != -1);
void	exec_pipe(char *block, t_ms *ms, int piping)
{
	ft_set_signals(1);
	if (piping && ms->pipeout[1] == -1)
		ft_pipe(ms, ms->pipeout);
	ft_addpid(ms);
	if (ft_fork(ms, &ms->last_pid->value))
		return ;
	if (!ms->last_pid->value)
	{
		ft_dup2(ms->pipein, 0);
		ft_close_pipe(ms->pipein);
		ft_dup2(ms->pipeout, 1);
		ft_close_pipe(ms->pipeout);
		if (!ms->error_file)
			lexer(block, ms, 0, 1);
		else
			g_ret_cmd = 1;
		exit(g_ret_cmd);
	}
	ft_close_pipe(ms->pipein);
	if (ms->pipeout[0] != -1)
		ft_set_pipe(ms->pipein, ms->pipeout[0], ms->pipeout[1]);
	else
		ft_close_pipe(ms->pipeout);
	ft_set_pipe(ms->pipeout, -1, -1);
}
