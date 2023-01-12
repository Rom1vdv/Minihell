/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:24:35 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/12 15:43:14 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	env_setascii(t_envp *envp, t_envp *target)
{
	int	lencmp;

	lencmp = ft_strlen(target->key);
	while (envp)
	{
		if (ft_strncmp(envp->key, target->key, lencmp) < 0)
			++target->ascii_pos;
		else
			++envp->ascii_pos;
		envp = envp->next;
	}
}

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
	res->key = splt[0];
	res->value = splt[1];
	res->ascii_pos = 0;
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
		env_setascii(res, tmp);
		++index;
	}
	return (res);
}

void	ft_setenv(t_envp *envp, char *target, char *value)
{
	int		targetlen;
	char	*join;
	t_envp	*tmp;

	if (!envp || !target || !value)
		return ;
	targetlen = ft_strlen(target) + 1;
	tmp = envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, target, targetlen))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		if (tmp->next)
			tmp = tmp->next;
		else
		{
			join = ft_strjoins(3, target, "=", value);
			if (!join)
				ft_perror("joins");
			tmp->next = envp_new(join);
			env_setascii(envp, tmp->next);
			return (free(join));
		}
	}
}

void	env_increment_shlvl(t_envp *envp)
{
	char	*value;

	value = ft_getenv(envp, "SHLVL");
	if (!value)
		return (ft_setenv(envp, "SHLVL", "1"));
	ft_setenv(envp, "SHLVL", ft_itoa(ft_atoi(value) + 1));
}
