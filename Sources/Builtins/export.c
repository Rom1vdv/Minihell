/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:35:24 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/16 11:27:07 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	display_sorted_env(t_envp *envp)
{
	int		index;
	int		size;
	t_envp	*tmp;

	size = ft_envplen(envp);
	index = 1;
	while (index < size + 1)
	{
		tmp = envp;
		while (tmp && tmp->ascii_pos != index)
			tmp = tmp->next;
		if (tmp && ft_strncmp(tmp->key, "_", 2))
			printf("%s=%s\n", tmp->key, tmp->value);
		++index;
	}
}

static void	ft_exportvar(t_envp *envp, char *target)
{
	int		targetlen;
	char	*join;
	t_envp	*tmp;

	if (!envp || !target)
		return ;
	targetlen = ft_strlen(target) + 1;
	tmp = envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, target, targetlen))
		{
			tmp->exported = 1;
			env_setascii(envp, tmp);
			return ;
		}
		if (tmp->next)
			tmp = tmp->next;
		else
		{
			join = ft_strjoin(target, "=");
			tmp->next = envp_new(join, 1);
			env_setascii(envp, tmp->next);
			return (free(join));
		}
	}
}

static void	ft_trimquotes(char *value)
{
	int		index;
	int		cpyndex;
	char	quote;

	index = 1;
	cpyndex = 1;
	quote = 0;
	while (value[index])
	{
		if (ft_strchr("'\"", value[index]))
		{
			if (!quote)
				quote = value[index];
			else if (value[index] == quote)
				quote = 0;
			else
				value[cpyndex++] = value[index];
		}
		else
			value[cpyndex++] = value[index];
		++index;
	}
	value[cpyndex] = '\0';
}

void	exec_export(t_ms *ms, char *line, int exported)
{
	char	*value;

	if (!ms || !ms->envp)
		return ;
	if (!line)
	{
		display_sorted_env(ms->envp);
		return ;
	}
	value = ft_strchr(line, '=');
	if (!value)
	{
		ft_exportvar(ms->envp, line);
		return ;
	}
	line[ft_strlen(line) - ft_strlen(value)] = '\0';
	ft_trimquotes(value);
	ft_setenv(ms->envp, line, &value[1], exported);
	ms->ret_cmd = 0;
}
