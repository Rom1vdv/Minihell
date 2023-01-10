/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:12:26 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/10 20:11:46 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	ft_free_node_envp(t_envp *free_me)
{
	free(free_me->head);
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
		printf("not enough arguments\n");
		return ;
	}
	targetlen = ft_strlen(target);
	if (!ft_strncmp(ms->envp->head, target, targetlen))
	{
		free_this = ms->envp;
		ms->envp = ms->envp->next;
		ft_free_node_envp(free_this);
		return ;
	}
	tmp = ms->envp;
	while (tmp->next)
	{
		if (!ft_strncmp(tmp->next->head, target, targetlen))
		{
			free_this = tmp->next;
			tmp->next = tmp->next->next;
			ft_free_node_envp(free_this);
			return ;
		}
		tmp = tmp->next;
	}
}
