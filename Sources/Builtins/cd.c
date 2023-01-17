/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:20:16 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/17 10:31:02 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/* step 5 in https://man7.org/linux/man-pages/man1/cd.1p.html */
static void	cat_cdpath(char curpath[255], char *directory, t_envp *envp)
{
	int		index;
	char	*path;
	char	**paths;
	DIR		*dir;

	path = ft_getenv(envp, "CDPATH");
	if (path)
	{
		paths = ft_split(path, ':');
		index = 0;
		while (paths[index])
		{
			if (paths[index][ft_strlen(paths[index]) - 1] == '/')
				path = ft_strjoin(paths[index], directory);
			else
				path = ft_strjoins(3, paths[index], "/", directory);
			dir = opendir(path);
			if (dir)
			{
				closedir(dir);
				ft_strcpy(curpath, path);
				ft_free_arr(paths);
				return (free(path));
			}
			else if (errno != ENOENT && errno != ENOTDIR) //dir exists but failed to open
				ft_perror(path);
			free(path);
			++index;
		}
		ft_free_arr(paths);
	}
	path = ft_strjoin("./", directory);
	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		ft_strcpy(curpath, path);
	}
	else if (errno != ENOENT && errno != ENOTDIR)
		ft_perror(path);
	free(path);
}

/* step 7 in https://man7.org/linux/man-pages/man1/cd.1p.html */
static void	cat_pwd(char curpath[255], t_envp *envp)
{
	char	*pwd;
	char	*path;

	pwd = ft_getenv(envp, "PWD");
	if (!pwd)
	{
		write(2, "you must first export PWD\n", 26);
		curpath[0] = '\0';
		return ;
	}
	if (pwd[ft_strlen(pwd) - 1] == '/')
		path = ft_strjoin(pwd, curpath);
	else
		path = ft_strjoins(3, pwd, "/", curpath);
	ft_strcpy(curpath, path);
	free(path);
}

/* step 8 in https://man7.org/linux/man-pages/man1/cd.1p.html */
static void	convert_canon(char *curpath)
{
	int	index;
	int	cpyndex;

	index = 0;
	cpyndex = 0;
	while (curpath[index])
	{
		if (curpath[index] == '.')
		{
			if (curpath[index + 1] == '/')
				++index;
			else if (curpath[index + 1] == '.')
			{
				++index;
				if (cpyndex > 1 && curpath[cpyndex - 1] == '/')
				{
					--cpyndex;
					curpath[cpyndex] = '\0';
					--cpyndex;
				}
				while (cpyndex > 0 && curpath[cpyndex] != '/')
				{
					curpath[cpyndex] = '\0';
					--cpyndex;
				}
			}
		}
		else if (curpath[index] == '/' && cpyndex > 0 && (curpath[cpyndex - 1] == '/' || !curpath[index + 1]));
		else
		{
			curpath[cpyndex] = curpath[index];
			++cpyndex;
		}
		++index;
	}
	curpath[cpyndex] = '\0';
}

void	exec_cd(char **lex, t_ms *ms)
{
	char	curpath[255];
	int		lexlen;
	char	*directory;

	ms->ret_cmd = 0;
	curpath[0] = '\0';
	lexlen = ft_arraylen(lex);
	if (lexlen == 1)
	{
		directory = ft_getenv(ms->envp, "HOME");
		if (!directory)
			return ;
	}
	else if (lexlen == 2)
		directory = lex[1];
	else
	{
		write(2, "-minishell: cd: too many arguments\n", 35); //check if this is the behavior, spoiler alert : it is not
		ms->ret_cmd = 1;
		return ;
	}
	ft_setenvpwd(ms->envp); //if pwd was unset, we reset it
	if (ft_strncmp(directory, "-", 2))
	{
		if (ft_strchr("/.", directory[0]))
			ft_strcpy(curpath, directory);
		else
			cat_cdpath(curpath, directory, ms->envp);
		if (!curpath[0])
		{
			directory = ft_strjoin("-minishell: cd: ", lex[1]);
			perror(directory);
			free(directory);
			ms->ret_cmd = 1;
			return ;
		}
		if (curpath[0] != '/')
		{
			cat_pwd(curpath, ms->envp);
			if (!curpath[0])
				return ;
		}
		convert_canon(curpath);
	}
	else
	{
		ft_strcpy(curpath, ft_getenv(ms->envp, "OLDPWD"));
		if (!curpath[0])
		{
			write(2, "-minishell: cd: OLDPWD not set\n", 31);
			ms->ret_cmd = 1;
			return ;
		}
	}
	// do we step 9 in https://man7.org/linux/man-pages/man1/cd.1p.html ????
	if (chdir(curpath) == -1)
	{
		directory = ft_strjoin("-minishell: cd: ", directory);
		perror(directory);
		free(directory);
		ms->ret_cmd = 1;
	}
	else
	{
		ft_setenv(ms->envp, "OLDPWD", ft_getenv(ms->envp, "PWD"), 1);
		ft_setenv(ms->envp, "PWD", curpath, 1);
	}
	if (!ft_strncmp(directory, "-", 2))
		printf("%s\n", curpath);
}
