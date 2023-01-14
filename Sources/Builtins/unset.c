/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:12:26 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/14 13:26:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	env_unsetascii(t_envp *envp, t_envp *target)
{
	int	lencmp;

	if (!target->exported)
		return ;
	lencmp = ft_strlen(target->key);
	while (envp)
	{
		if (envp->exported)
		{
			if (ft_strncmp(envp->key, target->key, lencmp) > 0)
				--envp->ascii_pos;
		}
		envp = envp->next;
	}
}

static void	ft_free_node_envp(t_envp *free_me)
{
	free(free_me->key);
	free(free_me->value);
	free(free_me);
}

void	exec_unset(t_ms *ms, char *target)
{
	int		targetlen;
	t_envp	*tmp;
	t_envp	*free_this;
	
	if (!ms || !ms->envp)
		return ;
	if (!target)
	{
		printf("unset: not enough arguments\n");
		ms->ret_cmd = 1;
		return ;
	}
	ms->ret_cmd = 0;
	targetlen = ft_strlen(target);
	if (!ft_strncmp(ms->envp->key, target, targetlen))
	{
		env_unsetascii(ms->envp, ms->envp);
		free_this = ms->envp;
		ms->envp = ms->envp->next;
		ft_free_node_envp(free_this);
		return ;
	}
	tmp = ms->envp;
	while (tmp->next)
	{
		if (!ft_strncmp(tmp->next->key, target, targetlen))
		{
			env_unsetascii(ms->envp, tmp->next);
			free_this = tmp->next;
			tmp->next = tmp->next->next;
			ft_free_node_envp(free_this);
			return ;
		}
		tmp = tmp->next;
	}
}
