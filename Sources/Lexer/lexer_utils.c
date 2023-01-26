/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 08:43:38 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/23 08:43:38 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	swap_quotes_arg(t_ms *ms, char *var)
{
	int		index;
	char	*join;

	index = ft_strlen(ms->rl);
	join = ft_strjoin(ms->rl, var);
	while (join[index])
	{
		if (join[index] == '\"')
			join[index] = 24;
		else if (join[index] == '\'')
			join[index] = 6;
		++index;
	}
	free(ms->rl);
	ms->rl = join;
}

static void	replace_arg(t_ms *ms, char **str, int *index)
{
	int		kindex;
	char	key[255];
	char	*var;

	kindex = 0;
	if ((*str)[*index] >= '0' && (*str)[*index] <= '9')
	{
		(*index)++;
		*str = &(*str)[*index];
		*index = 0;
		return ;
	}
	while ((*str)[*index] && !ft_strchr(" !&´^@$+°-#=~/:'\"", (*str)[*index]))
		key[kindex++] = (*str)[(*index)++];
	*str = &(*str)[*index];
	*index = 0;
	key[kindex] = '\0';
	var = ft_getenv(ms->envp, key);
	if (!var)
		return ;
	swap_quotes_arg(ms, var);
}

static void	ft_dollars(t_ms *ms, char **str, int *index)
{
	char	*var;
	char	*join;

	if ((*str)[*index] == '$')
	{
		var = ft_getenv(ms->envp, "SHLVL");
		*str = &(*str)[*index + 1];
		*index = 0;
		if (!var)
			return ;
		join = ft_strjoin(ms->rl, var);
		free(ms->rl);
		ms->rl = join;
	}
	else
		replace_arg(ms, str, index);
}

void	ft_joinvar(t_ms *ms, char **str, int *index)
{
	char	*var;
	char	*join;

	ft_joinfree(ms, str, index);
	if ((*str)[*index] == '?')
	{
		var = ft_itoa(g_ret_cmd);
		*str = &(*str)[*index + 1];
		*index = 0;
		join = ft_strjoin(ms->rl, var);
		free(ms->rl);
		ms->rl = join;
		free(var);
	}
	else
		ft_dollars(ms, str, index);
}

void	ft_joinfree(t_ms *ms, char **str, int *index)
{
	char	increment;
	char	*join;

	increment = (*str)[*index];
	(*str)[*index] = '\0';
	join = ft_strjoin(ms->rl, *str);
	free(ms->rl);
	ms->rl = join;
	if (increment)
		*str = &(*str)[*index + 1];
	*index = 0;
}
