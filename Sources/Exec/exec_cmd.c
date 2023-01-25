/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:15:40 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/25 17:33:31 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static char	*ft_get_cmdpath(char *cmd, char **paths)
{
	int		index;
	char	*res;

	if (cmd[0])
	{
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
	}
	ft_stderr("-minishell: ", cmd, NOTFOUND_ERR);
	free(cmd);
	return (0);
}

static void	noaccess_file(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == -1)
		ft_perror("stat");
	if ((statbuf.st_mode & S_IFMT) == S_IFDIR)
		ft_stderr("-minishell: ", path, ISDIR_ERR);
	else
		perror(path);
	exit(126);
}

static void	call_execve(t_ms *ms, char **cmds, int infork)
{
	int	pid;

	if (!infork)
	{
		ft_set_signals(1);
		if (ft_fork(ms, &pid))
			return ;
		if (!pid)
		{
			execve(cmds[0], cmds, ms->envp_dup);
			if (errno == EACCES)
				noaccess_file(cmds[0]);
			ft_perror(cmds[0]);
		}
		else
			ft_wait_child(pid);
	}
	else
	{
		execve(cmds[0], cmds, ms->envp_dup);
		if (errno == EACCES)
			noaccess_file(cmds[0]);
		ft_perror(cmds[0]);
	}
}

void	exec_cmd(t_ms *ms, char *path_lst, char **cmds, int infork)
{
	char	**paths;

	if (!cmds)
		return ;
	if (path_lst)
	{
		paths = ft_split(path_lst, ':');
		if (!access(cmds[0], F_OK))
			;
		else if (cmds[0][0] == '.')
		{
			ft_stderr("-minishell: ", cmds[0], NOFILE_ERR);
			free(cmds[0]);
			cmds[0] = 0;
		}
		else
			cmds[0] = ft_get_cmdpath(cmds[0], paths);
		ft_free_arr(paths);
	}
	if (!cmds[0])
	{
		g_ret_cmd = 127;
		return ;
	}
	call_execve(ms, cmds, infork);
}
