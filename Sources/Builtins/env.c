/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:25:36 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/12 10:11:53 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	exec_env(t_envp *envp)
{
	while (envp)
	{
		// printf("%d -> ", envp->ascii_pos);
		printf("%s=%s\n", envp->key, envp->value);
		envp = envp->next;
	}
}

char	*ft_getenv(t_envp *envp, char *target)
{
	int		targetlen;

	if (!envp || !target)
		return (0);
	targetlen = ft_strlen(target);
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
		ft_setenv(envp, "PWD", pwd);
}
