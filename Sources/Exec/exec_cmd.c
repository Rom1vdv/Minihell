/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:15:40 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/13 10:44:08 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	ft_wait_child(int pid, int *ret_cmd)
{
	int	wait;
	int	status;

	wait = waitpid(pid, &status, 0);
	if (wait == -1)
		return ;
	if (WIFEXITED(status))
		*ret_cmd = WEXITSTATUS(status);
}

static void	ft_fork(int *child_pid)
{
	*child_pid = fork();
	if (*child_pid == -1)
		ft_perror("fork");
}

static char	*ft_get_cmdpath(char *cmd, char **paths)
{
	int		index;
	char	*res;
	char	*joins;

	if (!access(cmd, X_OK))
		return (cmd);
	index = -1;
	while (paths[++index])
	{
		res = ft_strjoins(3, paths[index], "/", cmd);
		if (!access(res, X_OK))
		{
			free(cmd);
			return (res);
		}
		free(res);
	}
	joins = ft_strjoins(6, __FILE__, ": ", __func__, ": ",
			cmd, ": command not found\n");
	write(2, joins, ft_strlen(joins));
	free(joins);
	free(cmd);
	return (0);
}

void	exec_cmd(int *ret_cmd, char **envp, char *paths, char **cmds)
{
	int	pid;

	if (!cmds)
		return ;
	if (paths)
		cmds[0] = ft_get_cmdpath(cmds[0], ft_split(paths, ':'));
	if (!cmds[0])
		return ;
	ft_fork(&pid);
	if (!pid)
	{
		execve(cmds[0], cmds, envp);
		ft_perror(cmds[0]);
	}
	else
		ft_wait_child(pid, ret_cmd);
}
