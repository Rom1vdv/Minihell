/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:25:10 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/10 18:58:46 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_envp	*envp_new(char *line)
{
	t_envp	*res;
	char	**splt;

	if (!line)
		return (0);
	res = malloc(sizeof(*res));
	if (!res)
		ft_perror("env_init");
	splt = ft_split(line, '=');
	if (!splt)
		ft_perror("env_init");
	res->head = splt[0];
	res->value = splt[1];
	res->next = 0;
	free(splt);
	return (res);
}

t_envp	*env_init(char **envp)
{
	int		index;
	t_envp	*res;
	t_envp	*tmp;

	if (!envp || !envp[0])
		return (0);
	res = envp_new(envp[0]);
	tmp = res;
	index = 1;
	while (envp[index])
	{
		tmp->next = envp_new(envp[index]);
		tmp = tmp->next;
		++index;
	}
	return (res);
}

char	*ft_getenv(t_envp *envp, char *target)
{
	int		targetlen;

	if (!envp || !target)
		return (0);
	targetlen = ft_strlen(target);
	while (envp)
	{
		if (!ft_strncmp(envp->head, target, targetlen))
			return (envp->value);
		envp = envp->next;
	}
	return (0);
}

/* envp[of target]->value must be freed before calling this function */
void	ft_setenv(t_envp *envp, char *target, char *value)
{
	int		targetlen;
	char	*join;

	if (!envp || !target)
		return ;
	if (!value)
		ft_perror("strdup");
	targetlen = ft_strlen(target);
	while (envp)
	{
		if (!ft_strncmp(envp->head, target, targetlen))
		{
			envp->value = value;
			return ;
		}
		if (envp->next)
			envp = envp->next;
		else
		{
			join = ft_strjoins(3, target, "=", value);
			if (!join)
				ft_perror("joins");
			envp->next = envp_new(join);
			return (free(join));
		}
	}
}
