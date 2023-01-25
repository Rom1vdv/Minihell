/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:20:16 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/25 17:59:35 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

// do we step 9 in https://man7.org/linux/man-pages/man1/cd.1p.html ????
static void	jump_to_dir(t_ms *ms, char curpath[255], char *directory)
{
	if (chdir(curpath) == -1)
	{
		directory = ft_strjoin("-minishell: cd: ", directory);
		perror(directory);
		free(directory);
		g_ret_cmd = 1;
		return ;
	}
	else
	{
		ft_setenv(ms->envp, "OLDPWD", ft_getenv(ms->envp, "PWD"), 1);
		ft_setenv(ms->envp, "PWD", curpath, 1);
	}
	if (!ft_strncmp(directory, "-", 2))
		printf("%s\n", curpath);
}

static int	exec_cd_previous(t_ms *ms, char curpath[255])
{
	ft_strcpy(curpath, ft_getenv(ms->envp, "OLDPWD"));
	if (!curpath[0])
	{
		write(2, "-minishell: cd: OLDPWD not set\n", 31);
		g_ret_cmd = 1;
		return (1);
	}
	return (0);
}

static int	cdefault_case(t_ms *ms, char **lex, char *direc, char curpath[255])
{
	if (ft_strchr("/.", direc[0]))
		ft_strcpy(curpath, direc);
	else
		cd_catpath(curpath, direc, ms->envp, -1);
	if (!curpath[0])
	{
		direc = ft_strjoin("-minishell: cd: ", lex[1]);
		perror(direc);
		free(direc);
		g_ret_cmd = 1;
		return (1);
	}
	else if (curpath[0] != '/')
	{
		cd_catpwd(curpath, ms->envp);
		if (!curpath[0])
			return (1);
	}
	cd_convert_canon(curpath);
	return (0);
}

void	exec_cd(char **lex, t_ms *ms)
{
	char	curpath[255];
	int		lexlen;
	char	*directory;

	g_ret_cmd = 0;
	curpath[0] = '\0';
	lexlen = ft_arraylen(lex);
	if (lexlen == 1)
	{
		directory = ft_getenv(ms->envp, "HOME");
		if (!directory)
			return (ft_stderr("-minishell: cd: HOME not set\n", 0, 0));
	}
	else if (lexlen >= 2)
		directory = lex[1];
	ft_setenvpwd(ms->envp);
	if (ft_strncmp(directory, "-", 2))
	{
		if (cdefault_case(ms, lex, directory, curpath))
			return ;
	}
	else if (exec_cd_previous(ms, curpath))
		return ;
	jump_to_dir(ms, curpath, directory);
}
