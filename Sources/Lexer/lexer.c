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

static int	transform_meta_norm(t_ms *ms, char **str, int *index, char *quote)
{
	if (ft_strchr("'\"", (*str)[*index]))
	{
		if (!*quote)
			*quote = (*str)[*index];
		else if ((*str)[*index] == *quote)
			*quote = 0;
		if (*quote && (*str)[*index] != *quote)
			++(*index);
		else
			ft_joinfree(ms, str, index);
		return (1);
	}
	return (0);
}

/* using envp to transform $vars into their real value   *
*                          ~ into HOME variable of env   *
*                ignore ( and ) and ' and "              */
static void	transform_metachars(t_ms *ms, char *str)
{
	int		index;
	char	quote;

	ms->rl = NULL;
	index = 0;
	quote = 0;
	while (str[index])
	{
		if (transform_meta_norm(ms, &str, &index, &quote))
			;
		else if (str[index] == '$' && (!quote || quote == '\"')
			&& !ft_strchr("\" ", str[index + 1]))
			ft_joinvar(ms, &str, &index);
		else if (str[index] == '~' && !quote
			&& (index == 0 || str[index - 1] == ' ')
			&& (!str[index + 1] || str[index + 1] == ' '
				|| str[index + 1] == '/'))
			ft_joinhome(ms, &str, &index);
		else if (ft_strchr("()", str[index]) && !quote)
			ft_joinfree(ms, &str, &index);
		else
			++index;
	}
	ft_joinfree(ms, &str, &index);
}

static void	lexer_norm(t_ms *ms, char **lex, char *rl, int piping)
{
	if (!ft_strncmp(lex[0], "echo", 5))
		exec_echo(lex);
	else if (!ft_strncmp(lex[0], "cd", 3))
		exec_cd(lex, ms);
	else if (!ft_strncmp(lex[0], "pwd", 4))
		exec_pwd();
	else if (!ft_strncmp(lex[0], "export", 7))
		exec_export(ms, &lex[1], 1);
	else if (!ft_strncmp(lex[0], "unset", 6))
		exec_unset(ms, lex);
	else if (!ft_strncmp(lex[0], "env", 4))
		exec_env(ms->envp);
	else if (!ft_strncmp(lex[0], "exit", 5))
		exec_exit(lex, ms, rl, piping);
	else if (ft_strchr(lex[0], '=') && lex[0][0] != '=')
		exec_export(ms, lex, 0);
	else
	{
		ms->envp_dup = env_dup(ms->envp);
		exec_cmd(ms, ft_getenv(ms->envp, "PATH"), lex, piping);
		ft_free_arr(ms->envp_dup);
	}
}

void	lexer(char *rl, t_ms *ms, int index, int piping)
{
	int		sub_index;
	int		quote;
	char	**lex;

	lex = ft_split_quotes(rl, ' ');
	while (lex[index])
	{
		quote = !ft_strchr("'\"", lex[index][0]);
		transform_metachars(ms, lex[index]);
		free(lex[index]);
		lex[index] = ms->rl;
		if (!lex[index][0] && quote)
		{
			sub_index = index - 1;
			while (lex[++sub_index])
				lex[sub_index] = lex[sub_index + 1];
		}
		else
			++index;
	}
	if (lex[0])
		lexer_norm(ms, lex, rl, piping);
	else
		g_ret_cmd = 0;
	ft_free_arr(lex);
}
