/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:24:35 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/25 15:12:54 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	ft_setenv_match(t_envp *envp, t_envp *tmp, char *value, int export)
{
	char	*join;

	if (export > 1)
		join = ft_strjoin(tmp->value, value);
	else
		join = ft_strdup(value);
	free(tmp->value);
	tmp->value = ft_strdup(join);
	if (!tmp->exported && export % 2)
	{
		tmp->exported = export % 2;
		env_setascii(envp, tmp);
	}
	else if (tmp->exported == -1)
		tmp->exported = 1;
	free(join);
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
			return (ft_setenv_match(envp, tmp, value, exported));
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
	++res->ascii_pos;
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
