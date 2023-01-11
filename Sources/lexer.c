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

#include "../Includes/minishell.h"

static int	check_quotes(char *str)
{
	int		index;
	char	quote;

	index = 0;
	while (str[index])
	{
		if (ft_strchr("'\"", str[index]))
		{
			quote = str[index];
			++index;
			while (str[index] && str[index] != quote)
				++index;
			if (!str[index])
				return (1);
		}
		++index;
	}
	return (0);
}

static int	ft_catvar(t_ms *ms, int *cpyndex, char *str, int *index, char quote) //5args, because f*ck the norm
{
	char	key[255];
	char	*var;
	int		kindex;

	if (str[*index + 1] == '$')
	{
		++(*index);
		(*cpyndex) += 5;
		if (*cpyndex > 1023)
			return (*cpyndex);
		ft_strcpy(&ms->rl[*cpyndex - 5], "79862");
	}
	else
	{
		++(*index);
		kindex = 0;
		while (str[*index] && str[*index] != ' ' && str[*index] != '$' && str[*index] != quote)
			key[kindex++] = str[(*index)++];
		--(*index);
		key[kindex] = '\0';
		var = ft_getenv(ms->envp, key);
		if (var)
		{
			(*cpyndex) += ft_strlen(var);
			if (*cpyndex > 1023)
				return (*cpyndex);
			ft_strcpy(&ms->rl[*cpyndex - ft_strlen(var)], var);
		}
	}
	return (*cpyndex);
}

/* using envp to transform $vars to their real value          *
*  do not change if -> if -> else, it's meant to be like that */
static int	transform_metachars(t_ms *ms, char *str)
{
	int		index;
	int		cpyndex;
	char	quote;

	index = 0;
	cpyndex = 0;
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
		{
			if (ft_catvar(ms, &cpyndex, str, &index, quote) > 1023)
				return (cpyndex);
		}
		else
		{
			ms->rl[cpyndex++] = str[index];
			if (cpyndex > 1023)
				return (cpyndex);
		}
		++index;
	}
	ms->rl[cpyndex] = '\0';
	return (cpyndex);
}

void	lexer(char *rl, t_ms *ms)
{
	char	**lex;

	if (!rl[0])
		return ;
	if (check_quotes(rl))
	{
		printf("Unclosed quotes detected, pls fix\n");
		return ;
	}
	if (transform_metachars(ms, rl) > 1023)
	{
		printf("You exceded the maximum input size accepted, line must not exceed 1023 characters\n");
		return ;
	}
	lex = ft_split(ms->rl, ' ');
	if (!ft_strncmp(lex[0], "test", 5))
		test();
	else if (!ft_strncmp(lex[0], "echo", 5))
		exec_echo(lex, &ms->rl[4]);
	else if (!ft_strncmp(lex[0], "cd", 3))
		exec_cd(lex, ms);
	else if (!ft_strncmp(lex[0], "pwd", 4))
		printf("%s\n", ft_getenv(ms->envp, "PWD"));
	else if (!ft_strncmp(lex[0], "export", 7))
		exec_export(ms, lex[1]);
	else if (!ft_strncmp(lex[0], "unset", 6))
		exec_unset(ms, lex[1]);
	else if (!ft_strncmp(lex[0], "env", 4))
		display_env(ms->envp);
	else if (!ft_strncmp(lex[0], "exit", 5))
		close_program();
	else
		exec_cmd(ms->envp_original, ft_getenv(ms->envp, "PATH"), lex);
	ft_free_arr(lex);
}
