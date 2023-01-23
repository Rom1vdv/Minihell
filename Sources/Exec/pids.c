/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 08:43:29 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/23 08:43:29 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	ft_wait_child(int pid)
{
	int	wait;
	int	status;

	wait = waitpid(pid, &status, 0);
	if (wait == -1)
		return ;
	if (WIFEXITED(status))
		g_ret_cmd = WEXITSTATUS(status);
}

void	ft_addpid(t_ms *ms)
{
	t_pid	*tmp;

	tmp = ft_malloc(sizeof(*tmp), "addpid");
	tmp->next = 0;
	if (!ms->last_pid)
	{
		ms->pids = tmp;
		ms->last_pid = tmp;
	}
	else
	{
		ms->last_pid->next = tmp;
		ms->last_pid = ms->last_pid->next;
	}
}

void	ft_wait_pids(t_ms *ms)
{
	t_pid	*tmp;

	while (ms->pids)
	{
		tmp = ms->pids;
		ms->pids = ms->pids->next;
		ft_wait_child(tmp->value);
		free(tmp);
	}
	ms->pids = 0;
	ms->last_pid = 0;
}
