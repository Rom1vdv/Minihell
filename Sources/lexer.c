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

void	lexer(char *rl, t_ms *ms)
{
	char	**lex;

	if (!rl[0])
		return ;
	if (check_quotes(rl))
	{
		printf("Unclosed quotes detected, pls fix");
		return ;
	}
	lex = ft_split(rl, ' ');
	if (!ft_strncmp(lex[0], "test", 5))
		test();
	else if (!ft_strncmp(lex[0], "echo", 5))
		exec_echo(lex, &rl[4]);
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

/* I put this here for now */
int	check_quotes(char *str)
{
	int		index;
	int		quote;

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
