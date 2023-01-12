/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:35:24 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/12 13:26:40 by yhuberla         ###   ########.fr       */
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

int	ft_envplen(t_envp *envp)
{
	int	res;

	res = 0;
	while (envp)
	{
		++res;
		envp = envp->next;
	}
	return (res);
}

void	exec_export(t_ms *ms, char *line)
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
		return ;
	line[ft_strlen(line) - ft_strlen(value)] = '\0';
	ft_setenv(ms->envp, line, &value[1]);
}
