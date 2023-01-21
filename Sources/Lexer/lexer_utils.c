// add header here

#include "../../Includes/minishell.h"

static void	ft_joinvar_norm2(t_ms *ms, char **str, int *index)
{
	int		kindex;
	char	key[255];
	char	*var;
	char	*join;

	kindex = 0;
	if ((*str)[*index] >= '0' && (*str)[*index] <= '9')
	{
		(*index)++;
		*str = &(*str)[*index];
		return ;
	}
	while ((*str)[*index] && !ft_strchr(" !&´^@$+°-#=~/'\"", (*str)[*index]))
		key[kindex++] = (*str)[(*index)++];
	*str = &(*str)[*index];
	*index = 0;
	key[kindex] = '\0';
	var = ft_getenv(ms->envp, key);
	if (!var)
		return ;
	join = ft_strjoin(ms->rl, var);
	free(ms->rl);
	ms->rl = join;
}

static void	ft_joinvar_norm(t_ms *ms, char **str, int *index)
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
		ft_joinvar_norm2(ms, str, index);
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
		ft_joinvar_norm(ms, str, index);
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
