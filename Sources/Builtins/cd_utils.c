/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 08:43:05 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/23 08:43:05 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static int	cdpath_match(char curpath[255], char **paths, char *direc, int indx)
{
	char	*path;
	DIR		*dir;

	if (paths[indx][ft_strlen(paths[indx]) - 1] == '/')
		path = ft_strjoin(paths[indx], direc);
	else
		path = ft_strjoins(3, paths[indx], "/", direc);
	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		ft_strcpy(curpath, path);
		ft_free_arr(paths);
		free(path);
		return (1);
	}
	else if (errno != ENOENT && errno != ENOTDIR)
		ft_perror(path);
	free(path);
	return (0);
}

static void	cd_handle_dots(char *curpath, int *index, int *cpyndex)
{
	if (curpath[*index + 1] == '/')
		++(*index);
	else if (curpath[*index + 1] == '.')
	{
		++(*index);
		if (*cpyndex > 1 && curpath[*cpyndex - 1] == '/')
		{
			--(*cpyndex);
			curpath[*cpyndex] = '\0';
			--(*cpyndex);
		}
		while (*cpyndex > 1 && curpath[*cpyndex] != '/')
			--(*cpyndex);
		curpath[*cpyndex] = '\0';
	}
}

/* step 8 in https://man7.org/linux/man-pages/man1/cd.1p.html */
void	cd_convert_canon(char *curpath)
{
	int	index;
	int	cpyndex;

	index = 0;
	cpyndex = 0;
	while (curpath[index])
	{
		if (curpath[index] == '.')
			cd_handle_dots(curpath, &index, &cpyndex);
		else if (curpath[index] == '/' && cpyndex > 0
			&& (curpath[cpyndex - 1] == '/' || !curpath[index + 1]))
			;
		else
		{
			curpath[cpyndex] = curpath[index];
			++cpyndex;
		}
		++index;
	}
	curpath[cpyndex] = '\0';
}

/* step 5 in https://man7.org/linux/man-pages/man1/cd.1p.html */
void	cd_catpath(char curpath[255], char *directory, t_envp *envp, int index)
{
	char	*path;
	char	**paths;
	DIR		*dir;

	path = ft_getenv(envp, "CDPATH");
	if (path)
	{
		paths = ft_split(path, ':');
		while (paths[++index])
		{
			if (cdpath_match(curpath, paths, directory, index))
				return ;
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
void	cd_catpwd(char curpath[255], t_envp *envp)
{
	char	*pwd;
	char	*path;

	pwd = ft_getenv(envp, "PWD");
	if (!pwd)
	{
		write(2, "-minishell: you must first export PWD\n", 39);
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
