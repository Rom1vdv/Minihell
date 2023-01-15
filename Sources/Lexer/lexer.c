/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 09:47:52 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/10 09:47:52 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	ft_joinfree(t_ms *ms, char **strptr, int *index)
{
	char	increment;
	char	*join;

	increment = (*strptr)[*index];
	(*strptr)[*index] = '\0';
	join = ft_strjoin(ms->rl, *strptr);
	free(ms->rl);
	ms->rl = join;
	if (increment)
		*strptr = &(*strptr)[*index + 1];
	*index = 0;
}

static void	ft_joinvar(t_ms *ms, char **strptr, int *index, char quote)
{
	int		kindex;
	char	key[255];
	char	*var;
	char	*join;

	ft_joinfree(ms, strptr, index);
	if ((*strptr)[*index] == '?')
	{
		var = ft_itoa(ms->ret_cmd);
		*strptr = &(*strptr)[*index + 1];
		*index = 0;
		join = ft_strjoin(ms->rl, var);
		free(ms->rl);
		ms->rl = join;
		free(var);
	}
	else if ((*strptr)[*index] == '$')
	{
		var = ft_getenv(ms->envp, "SHLVL");
		*strptr = &(*strptr)[*index + 1];
		*index = 0;
		if (!var)
			return ;
		join = ft_strjoin(ms->rl, var);
		free(ms->rl);
		ms->rl = join;
	}
	else
	{
		kindex = 0;
		while ((*strptr)[*index] && (*strptr)[*index] != ' ' && (*strptr)[*index] != '$' && (*strptr)[*index] != quote)
			key[kindex++] = (*strptr)[(*index)++];
		*strptr = &(*strptr)[*index];
		*index = 0;
		key[kindex] = '\0';
		var = ft_getenv(ms->envp, key);
		if (!var)
			return ;
		join = ft_strjoin(ms->rl, var);
		free(ms->rl);
		ms->rl = join;
	}

}

static void	ft_joinhome(t_ms *ms, char **strptr, int *index)
{
	char	*var;
	char	*join;

	ft_joinfree(ms, strptr, index);
	var = ft_getenv(ms->envp, "HOME");
	if (!var)
		return ;
	join = ft_strjoin(ms->rl, var);
	free(ms->rl);
	ms->rl = join;
}

/* using envp to transform $vars into their real value   *
*                          ~ into HOME variable of env   *
*                ignore ( and )                          */
static void	transform_metachars(t_ms *ms, char *str)
{
	int		index;
	char	quote;

	ms->rl = NULL;
	index = 0;
	quote = 0;
	while (str[index])
	{
		if (ft_strchr("'\"", str[index]))
		{
			if (!quote)
				quote = str[index];
			else if (str[index] == quote)
				quote = 0;
		}
		if (str[index] == '$' && (!quote || quote == '\"') && str[index + 1] != ' ' && str[index + 1])
			ft_joinvar(ms, &str, &index, quote);
		else if (str[index] == '~' && !quote && (index == 0 || str[index - 1] == ' ') && (!str[index + 1] || str[index + 1] == ' ' || str[index + 1] == '/'))
			ft_joinhome(ms, &str, &index);
		else if (ft_strchr("()", str[index]) && !quote)
			ft_joinfree(ms, &str, &index);
		else
			++index;
	}
	ft_joinfree(ms, &str, &index);
}

void	lexer(char *rl, t_ms *ms)
{
	char	**lex;
	char	**envp_dup;

	transform_metachars(ms, rl);
	lex = ft_split_quotes(ms->rl, ' ');
	if (!ft_strncmp(lex[0], "test", 5))
		test(ms);
	else if (!ft_strncmp(lex[0], "echo", 5))
		exec_echo(lex, &ms->rl[4], &ms->ret_cmd);
	else if (!ft_strncmp(lex[0], "cd", 3))
		exec_cd(lex, ms);
	else if (!ft_strncmp(lex[0], "pwd", 4))
		exec_pwd(&ms->ret_cmd);
	else if (!ft_strncmp(lex[0], "export", 7))
		exec_export(ms, lex[1], 1);
	else if (!ft_strncmp(lex[0], "unset", 6))
		exec_unset(ms, lex[1]);
	else if (!ft_strncmp(lex[0], "env", 4))
		exec_env(ms->envp, &ms->ret_cmd);
	else if (!ft_strncmp(lex[0], "exit", 5))
		close_program(ms->envp, rl);
	else if (ft_strchr(lex[0], '=') && lex[0][0] != '=')
		exec_export(ms, lex[0], 0);
	else
	{
		envp_dup = env_dup(ms->envp);
		exec_cmd(&ms->ret_cmd, envp_dup, ft_getenv(ms->envp, "PATH"), lex);
		ft_free_arr(envp_dup);
	}
	free(ms->rl);
	ft_free_arr(lex);
}

// static int	ft_catvar(t_ms *ms, int *cpyndex, char *str, int *index, char quote) //5args, because f*ck the norm
// {
// 	char	key[255];
// 	char	*var;
// 	int		kindex;

// 	if (str[*index + 1] == '?')
// 	{
// 		++(*index);
// 		var = ft_itoa(ms->ret_cmd);
// 		if (var)
// 		{
// 			(*cpyndex) += ft_strlen(var);
// 			if (*cpyndex > 1023)
// 			{
// 				free(var);
// 				return (*cpyndex);
// 			}
// 			ft_strcpy(&ms->rl[*cpyndex - ft_strlen(var)], var);
// 			free(var);
// 		}
// 	}
// 	else if (str[*index + 1] == '$')
// 	{
// 		++(*index);
// 		(*cpyndex) += 5;
// 		if (*cpyndex > 1023)
// 			return (*cpyndex);
// 		ft_strcpy(&ms->rl[*cpyndex - 5], "79862");
// 	}
// 	else
// 	{
// 		++(*index);
// 		kindex = 0;
// 		while (str[*index] && str[*index] != ' ' && str[*index] != '$' && str[*index] != quote)
// 			key[kindex++] = str[(*index)++];
// 		--(*index);
// 		key[kindex] = '\0';
// 		var = ft_getenv(ms->envp, key);
// 		if (var)
// 		{
// 			(*cpyndex) += ft_strlen(var);
// 			if (*cpyndex > 1023)
// 				return (*cpyndex);
// 			ft_strcpy(&ms->rl[*cpyndex - ft_strlen(var)], var);
// 		}
// 	}
// 	return (*cpyndex);
// }

// static int	ft_cathome(t_ms *ms, int *cpyndex)
// {
// 	char	*var;

// 	var = ft_getenv(ms->envp, "HOME");
// 	if (var)
// 	{
// 		(*cpyndex) += ft_strlen(var);
// 		if (*cpyndex > 1023)
// 			return (*cpyndex);
// 		ft_strcpy(&ms->rl[*cpyndex - ft_strlen(var)], var);
// 	}
// 	return (*cpyndex);
// }

// static int	transform_metachars(t_ms *ms, char *str)
// {
// 	int		index;
// 	int		cpyndex;
// 	char	quote;

// 	index = 0;
// 	cpyndex = 0;
// 	quote = 0;
// 	while (str[index])
// 	{
// 		if (ft_strchr("'\"", str[index]))
// 		{
// 			if (!quote)
// 				quote = str[index];
// 			else if (str[index] == quote)
// 				quote = 0;
// 		}
// 		if (str[index] == '$' && (!quote || quote == '\"') && str[index + 1] != ' ' && str[index + 1])
// 		{
// 			if (ft_catvar(ms, &cpyndex, str, &index, quote) > 1023)
// 				return (cpyndex);
// 		}
// 		else if (str[index] == '~' && !quote && (index == 0 || str[index - 1] == ' ') && (!str[index + 1] || str[index + 1] == ' ' || str[index + 1] == '/'))
// 		{
// 			if (ft_cathome(ms, &cpyndex) > 1023)
// 				return (cpyndex);
// 		}
// 		else if (ft_strchr("()", str[index]) && !quote);
// 		else
// 		{
// 			ms->rl[cpyndex++] = str[index];
// 			if (cpyndex > 1023)
// 				return (cpyndex);
// 		}
// 		++index;
// 	}
// 	ms->rl[cpyndex] = '\0';
// 	return (cpyndex);
// }
