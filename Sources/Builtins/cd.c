/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:20:16 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/11 11:17:10 by yhuberla         ###   ########.fr       */
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
		if (!paths)
			ft_perror("split");
		index = 0;
		while (paths[index])
		{
			if (paths[index][ft_strlen(paths[index] - 1)] == '/')
				path = ft_strjoin(paths[index], directory);
			else
				path = ft_strjoins(3, paths[index], "/", directory);
			if (!path)
				ft_perror("join");
			dir = opendir(path);
			if (dir)
			{
				closedir(dir);
				ft_strcpy(curpath, path);
				ft_free_arr(paths);
				return (free(path));
			}
			else if (errno != ENOENT) //dir exists but failed to open
				ft_perror(path);
			free(path);
			++index;
		}
		ft_free_arr(paths);
	}
	path = ft_strjoin("./", directory);
	if (!path)
		ft_perror("join");
	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		ft_strcpy(curpath, path);
		free(path);
	}
	else if (errno != ENOENT)
		ft_perror(path);
}

/* step 7 in https://man7.org/linux/man-pages/man1/cd.1p.html */
static void	cat_pwd(char curpath[255], t_envp *envp)
{
	char	*pwd;
	char	*path;

	pwd = ft_getenv(envp, "PWD");
	if (!pwd)
	{
		printf("you must first export PWD\n");
		curpath[0] = '\0';
		return ;
	}
	if (pwd[ft_strlen(pwd) - 1] == '/')
		path = ft_strjoin(pwd, curpath);
	else
		path = ft_strjoins(3, pwd, "/", curpath);
	if (!path)
		ft_perror("join");
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
		printf("cd: too many arguments\n"); //check if this is the behavior, spoiler alert : it is not
		return ;
	}
	if (ft_strncmp(directory, "-", 2))
	{
		if (ft_strchr("/.", directory[0]))
			ft_strcpy(curpath, directory);
		else
			cat_cdpath(curpath, directory, ms->envp);
		if (!curpath[0])
		{
			directory = ft_strjoin("-bash: cd: ", lex[1]);
			perror(directory);
			free(directory);
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
		ft_strcpy(curpath, ft_getenv(ms->envp, "OLDPWD"));
	// do we step 9 in https://man7.org/linux/man-pages/man1/cd.1p.html ????
	ft_setenvpwd(ms->envp); //if pwd was unset, we reset it
	if (chdir(curpath) == -1)
	{
		directory = ft_strjoin("-bash: cd: ", curpath); //or join with lex[1] to mimic real msg ??
		perror(directory);
		free(directory);
	}
	else
	{
		ft_setenv(ms->envp, "OLDPWD", ft_getenv(ms->envp, "PWD"));
		ft_setenv(ms->envp, "PWD", curpath);
	}
	if (!ft_strncmp(directory, "-", 2))
		printf("%s\n", curpath);
}


/**
 * It changes the current working directory to the one specified in the first argument of the command
 * 
 * @param lex the array of strings that are the command and its arguments
 * @param ms a structure that contains the previous pwd
 */
// void	exec_cd(char **lex, t_ms *ms)
// {
// 	char	*msg;
// 	char	tmp_pwd[255];
// 	char	new_pwd[255];
// 	int		ret_cd;

// 	ret_cd = 0;
// 	printf("prev before : %s\n", ms->prev_pwd);
// 	getcwd(tmp_pwd, sizeof(tmp_pwd));
// 	if (ft_arraylen(lex) > 2)
// 		printf("-bash: cd: too many arguments\n");
// 	else if (!ft_strncmp(lex[1], "-", 2))
// 	{
// 		if (!ms->prev_pwd)
// 			printf("there is no previous pwd\n");
// 		else
// 			ret_cd = chdir(ms->prev_pwd);
// 	}
// 	else 
// 		ret_cd = chdir(lex[1]);
// 	if (ret_cd == -1)
// 	{
// 		msg = ft_strjoin("-bash: cd: ", lex[1]);
// 		perror(msg);
// 		free(msg);
// 	}
// 	else
// 	{
// 		getcwd(new_pwd, sizeof(new_pwd));
// 		printf("old : %s, new : %s\n", tmp_pwd, new_pwd);
// 		ms->prev_pwd = tmp_pwd;
// 	}
// 	printf("prev after : %s\n", ms->prev_pwd);
// }
