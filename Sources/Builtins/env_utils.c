/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:24:35 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/19 10:10:15 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	env_setascii(t_envp *envp, t_envp *target)
{
	int	lencmp;

	if (!target->exported)
		return ;
	lencmp = ft_strlen(target->key);
	while (envp)
	{
		if (envp->exported)
		{
			if (ft_strncmp(envp->key, target->key, lencmp) < 0)
				++target->ascii_pos;
			else
				++envp->ascii_pos;
		}
		envp = envp->next;
	}
}

t_envp	*envp_new(char *line, int exported)
{
	t_envp	*res;
	char	**splt;

	if (!line)
		return (0);
	res = ft_malloc(sizeof(*res), "env_init");
	splt = ft_split_first(line, '=');
	res->key = ft_strdup(splt[0]);
	res->value = ft_strdup(splt[1]);
	res->ascii_pos = 0;
	res->exported = exported;
	res->next = 0;
	ft_free_arr(splt);
	return (res);
}

t_envp	*env_init(char **envp)
{
	int		index;
	t_envp	*res;
	t_envp	*tmp;

	if (!envp || !envp[0])
		return (0);
	res = envp_new(envp[0], 1);
	tmp = res;
	index = 1;
	while (envp[index])
	{
		tmp->next = envp_new(envp[index], 1);
		tmp = tmp->next;
		env_setascii(res, tmp);
		++index;
	}
	return (res);
}

void	ft_setenv(t_envp *envp, char *target, char *value, int exported)
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
			join = value;
			if (exported > 1)
				join = ft_strjoin(tmp->value, value);
			free(tmp->value);
			tmp->value = ft_strdup(join);
			if (!tmp->exported && exported % 2)
			{
				tmp->exported = exported % 2;
				env_setascii(envp, tmp);
			}
			return ;
		}
		if (tmp->next)
			tmp = tmp->next;
		else
		{
			join = ft_strjoins(3, target, "=", value);
			tmp->next = envp_new(join, exported % 2);
			env_setascii(envp, tmp->next);
			return (free(join));
		}
	}
}

void	env_increment_shlvl(t_envp *envp)
{
	int		shlvl;
	char	*value;
	char	*new_value;

	value = ft_getenv(envp, "SHLVL");
	if (!value)
		return (ft_setenv(envp, "SHLVL", "1", 1));
	shlvl = ft_atoi(value);
	if (shlvl < 0)
		shlvl = -1;
	new_value = ft_itoa(shlvl + 1);
	ft_setenv(envp, "SHLVL", new_value, 1);
	free(new_value);
}
