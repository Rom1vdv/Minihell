/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:15:40 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/19 08:54:55 by yhuberla         ###   ########.fr       */
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

	if (cmd && cmd[0])
	{
		if (!access(cmd, F_OK))
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
	}
	msg = ft_strjoin(cmd, ": command not found\n");
	write(2, msg, ft_strlen(msg));
	free(msg);
	free(cmd);
	return (0);
}

static void	noaccess_file(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == -1)
		ft_perror("stat");
	if ((statbuf.st_mode & S_IFMT) == S_IFDIR)
	{
		write(2, path, ft_strlen(path));
		write(2, ": is a directory\n", 17);
	}
	else
		perror(path);
	exit(126);
}

void	exec_cmd(char **envp, char *path_lst, char **cmds)
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
		g_ret_cmd = 127;
		return ;
	}
	ft_fork(&pid);
	if (!pid)
	{
		execve(cmds[0], cmds, envp);
		if (errno == EACCES) // may want to check if cmds[0] is a dir to handle ~ for ex
			noaccess_file(cmds[0]);
		ft_perror(cmds[0]);
	}
	else
		ft_wait_child(pid);
}
