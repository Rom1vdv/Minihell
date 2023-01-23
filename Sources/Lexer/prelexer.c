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
	char	**pipes;

	ft_set_pipe(ms->pipein, -1, -1);
	ft_set_pipe(ms->pipeout, -1, -1);
	pipes = ft_split_quotes(block, '|');
	if (ft_arraylen(pipes) > 1)
	{
		index = 0;
		while (pipes[index])
		{
			ft_handle_redirs(pipes[index], ms, 1, pipes[index + 1] != 0);
			++index;
		}
	}
	else
		ft_handle_redirs(block, ms, 0, 0);
	ft_close_pipe(ms->pipein);
	ft_close_pipe(ms->pipeout);
	ft_free_arr(pipes);
	ft_wait_pids(ms);
}

void	prelexer(char *rl, t_ms *ms)
{
	int		index;
	char	**semicolons;

	if (check_parse_error(rl))
	{
		g_ret_cmd = 2;
		return ;
	}
	index = 0;
	semicolons = ft_split_quotes(rl, ';');
	while (semicolons[index])
	{
		exec_block(ms, semicolons[index]);
		++index;
	}
	ft_free_arr(semicolons);
}

	// printf("cmd = %s\n", block);
	// printf("pipein : [%d, %d], pipeout : [%d, %d]\n", ms->pipein[0],
	// 	ms->pipein[1], ms->pipeout[0], ms->pipeout[1]);
	// printf("is %d open ? %d\n", ms->pipein[0], fcntl(ms->pipein[0], 
		//F_GETFD) != -1);
	// printf("is %d open ? %d\n", ms->pipeout[1], fcntl(ms->pipeout[1], 
		//F_GETFD) != -1);
void	exec_pipe(char *block, t_ms *ms, int piping)
{
	ft_set_signals(ms, 1);
	if (piping && ms->pipeout[1] == -1)
		ft_pipe(ms->pipeout);
	ft_addpid(ms);
	ft_fork(&ms->last_pid->value);
	if (!ms->last_pid->value)
	{
		ft_dup2(ms->pipein, 0);
		ft_close_pipe(ms->pipein);
		ft_dup2(ms->pipeout, 1);
		ft_close_pipe(ms->pipeout);
		lexer(block, ms, 0, 1);
		exit(g_ret_cmd);
	}
	if (ms->pipeout[0] != -1 || (ms->pipeout[1] != -1))
	{
		ft_close_pipe(ms->pipein);
		ft_set_pipe(ms->pipein, ms->pipeout[0], ms->pipeout[1]);
	}
	else
		ft_close_pipe(ms->pipeout);
	ft_set_pipe(ms->pipeout, -1, -1);
}
