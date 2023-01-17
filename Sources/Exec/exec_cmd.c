/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:15:40 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/17 11:22:29 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/* list of modifs to be done :                                        *
 *   ./ls -> bash: ./ls: No such file or directory                    *
 *   "" -> bash: : command not found                                  *
 *   chmod -x exec, ./exec -> bash: ./minishellbis: Permission denied */
static char	*ft_get_cmdpath(char *cmd, char **paths) //modif to do
{
	int		index;
	char	*res;
	char	*msg;

	if (!access(cmd, X_OK))
		return (cmd);
	if (!access(cmd, F_OK))
	{
		msg = ft_strjoin(cmd, ": permission denied\n");
		write(2, msg, ft_strlen(msg));
		free(msg);
		free(cmd);
		exit(126);
	}
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
	msg = ft_strjoin(cmd, ": command not found\n");
	write(2, msg, ft_strlen(msg));
	free(msg);
	free(cmd);
	return (0);
}

void	exec_cmd(int *ret_cmd, char **envp, char *path_lst, char **cmds)
{
	int	pid;
	char	**paths;

	if (!cmds)
		return ;
	if (path_lst)
	{
		paths = ft_split(path_lst, ':');
		cmds[0] = ft_get_cmdpath(cmds[0], paths);
		ft_free_arr(paths);
	}
	if (!cmds[0])
	{
		*ret_cmd = 127;
		return ;
	}
	ft_fork(&pid);
	if (!pid)
	{
		execve(cmds[0], cmds, envp);
		if (errno == EACCES)
		{
			perror(cmds[0]);
			exit(126);
		}
		ft_perror(cmds[0]);
	}
	else
		ft_wait_child(pid, ret_cmd);
}
