/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:25:36 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/14 14:24:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	exec_env(t_envp *envp, int *ret_cmd)
{
	while (envp)
	{
		// printf("%-3d-> ", envp->ascii_pos);
		if (envp->exported)
			printf("%s=%s\n", envp->key, envp->value);
		envp = envp->next;
	}
	*ret_cmd = 0;
}

/* loops through envp and return the value associated to the key "target" *
*  if it exits, return NULL otherwise                                     */
char	*ft_getenv(t_envp *envp, char *target)
{
	int		targetlen;

	if (!envp || !target)
		return (0);
	targetlen = ft_strlen(target) + 1;
	while (envp)
	{
		if (!ft_strncmp(envp->key, target, targetlen))
			return (envp->value);
		envp = envp->next;
	}
	return (0);
}

void	ft_setenvpwd(t_envp *envp)
{
	char	pwd[255];

	if (getcwd(pwd, sizeof(pwd)))
		ft_setenv(envp, "PWD", pwd, 1);
}

char	**env_dup(t_envp *envp)
{
	int		index;
	int		envlen;
	char	**res;

	envlen = ft_envplen(envp);
	res = ft_malloc(sizeof(*res) * (envlen + 1), "env_dup");
	index = 0;
	while (envp)
	{
		if (envp->exported)
			res[index++] = ft_strjoins(3, envp->key, "=", envp->value);
		envp = envp->next;
	}
	res[index] = 0;
	return (res);
}
