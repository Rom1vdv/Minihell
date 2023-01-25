/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forkpipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 09:54:19 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/25 17:00:10 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/* ms->error_fork is 1 if pipe() failed, put the verif here for norming */
int	ft_fork(t_ms *ms, int *child_pid)
{
	if (ms->error_fork)
		return (1);
	*child_pid = fork();
	if (*child_pid == -1)
	{
		ft_close_pipe(ms->pipein);
		ft_close_pipe(ms->pipeout);
		ms->error_fork = 1;
		perror("fork");
		return (1);
	}
	return (0);
}

void	ft_pipe(t_ms *ms, int pipefd[2])
{
	int	pipe_ret;

	pipe_ret = pipe(pipefd);
	if (pipe_ret == -1)
	{
		ft_close_pipe(ms->pipein);
		ft_close_pipe(ms->pipeout);
		ms->error_fork = 1;
		perror("pipe");
	}
}

void	ft_close_pipe(int pipefd[2])
{
	if (pipefd[0] != -1)
		close(pipefd[0]);
	if (pipefd[1] != -1)
		close(pipefd[1]);
}

void	ft_set_pipe(int pipefd[2], int in, int out)
{
	pipefd[0] = in;
	pipefd[1] = out;
}

void	ft_dup2(int pipefd[2], int fd)
{
	int	dup_ret;

	if (pipefd[fd] == -1)
		return ;
	dup_ret = dup2(pipefd[fd], fd);
	if (dup_ret == -1)
		ft_perror("dup2");
}
