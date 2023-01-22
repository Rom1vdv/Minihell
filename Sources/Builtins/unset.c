/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:12:26 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/22 14:49:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	env_unsetascii(t_envp *envp, t_envp *target)
{
	int	lencmp;

	if (!target->exported)
		return ;
	lencmp = ft_strlen(target->key) + 1;
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

t_envp	*ft_free_node_envp(t_envp *tmp)
{
	t_envp	*free_me;

	free_me = tmp;
	tmp = tmp->next;
	free(free_me->key);
	free(free_me->value);
	free(free_me);
	return (tmp);
}

static void	handle_unset_args(t_ms *ms, char *target)
{
	int		targetlen;
	t_envp	*tmp;

	g_ret_cmd = 0;
	targetlen = ft_strlen(target) + 1;
	if (!ft_strncmp(ms->envp->key, target, targetlen))
	{
		env_unsetascii(ms->envp, ms->envp);
		ms->envp = ft_free_node_envp(ms->envp);
		return ;
	}
	tmp = ms->envp;
	while (tmp->next)
	{
		if (!ft_strncmp(tmp->next->key, target, targetlen))
		{
			env_unsetascii(ms->envp, tmp->next);
			tmp->next = ft_free_node_envp(tmp->next);
			return ;
		}
		tmp = tmp->next;
	}
}

void	exec_unset(t_ms *ms, char **target_array)
{
	int		index;
	char	*t;

	index = 1;
	if (!ms || !ms->envp)
		return ;
	if (!target_array[1])
		return ;
	while (target_array[index])
	{
		t = target_array[index];
		if (ft_strchr("0123456789-=", t[0]) || ft_strchr(t, ':')
			|| ft_strchr(t, '-') || ft_strchr(t, '\\') || ft_strchr(t, '.')
			|| ft_strchr(t, '+') || ft_strchr(t, '$') || ft_strchr(t, '}')
			|| ft_strchr(t, '{') || ft_strchr(t, '*') || ft_strchr(t, '#')
			|| ft_strchr(t, '@') || ft_strchr(t, '!') || ft_strchr(t, '^')
			|| ft_strchr(t, '~') || ft_strchr(t, '='))
		{
			ft_stderr("-minishell: unset: ", t, EXPORT_ERR);
			g_ret_cmd = 1 + (t[0] == '-');
		}
		else
			handle_unset_args(ms, target_array[index]);
		++index;
	}
}
