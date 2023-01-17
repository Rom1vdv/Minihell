/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forkpipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 09:54:19 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/17 16:43:34 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	ft_wait_child(int pid, int *ret_cmd)
{
	int	wait;
	int	status;

	wait = waitpid(pid, &status, 0);
	if (wait == -1)
		return ;
	if (WIFEXITED(status))
		*ret_cmd = WEXITSTATUS(status);
}

void	ft_fork(int *child_pid)
{
	*child_pid = fork();
	if (*child_pid == -1)
		ft_perror("fork");
}

void	ft_pipe(int pipefd[2])
{
	int	pipe_ret;

	pipe_ret = pipe(pipefd);
	if (pipe_ret == -1)
		ft_perror("pipe");
}

void	ft_close_pipe(int pipefd[2])
{
	close(pipefd[0]);
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

	// printf("dup2 at %d : %d\n", fd, pipefd[fd]);
	if (pipefd[fd] == -1)
		return ;
	dup_ret = dup2(pipefd[fd], fd);
	if (dup_ret == -1)
		ft_perror("dup2");
}
