/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:26:09 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/11 11:26:09 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

// static void	print_echo(char *str)
// {
// 	int		index;
// 	char	quote;

// 	index = 0;
// 	quote = 0;
// 	while (str[++index])
// 	{
// 		if (ft_strchr("'\"", str[index]))
// 		{
// 			if (!quote)
// 				quote = str[index];
// 			else if (str[index] == quote)
// 				quote = 0;
// 			else
// 				write(1, &str[index], 1);
// 		}
// 		else if (quote || str[index] != ' ')
// 			write(1, &str[index], 1);
// 		else if (str[index - 1] != ' ')
// 			write(1, " ", 1);
// 	}
// }

static int	ft_check_option(char *lex)
{
	int	index;

	if (lex[0] != '-')
		return (0);
	index = 1;
	while (lex[index])
	{
		if (lex[index] != 'n')
			return (0);
		++index;
	}
	return (1);
}
/**
 * It prints the arguments passed to it, with the option to not print a newline at the end
 * 
 * @param lex array of strings, each string is a word in the command line
 * @param args "-n hello world"
 */

void	exec_echo(char **lex)
{
	int		option;
	int		index;

	if (!lex[1])
		return (ft_putendl(""));
	option = ft_check_option(lex[1]);//(!ft_strncmp(lex[1], "-n", 3));
	index = option + 1;
	while (lex[index] && ft_check_option(lex[index]))
		++index;
	while (lex[index])
	{
		printf("%s", lex[index]);
		if (lex[index + 1])
			printf(" ");
		++index;
	}
	if (!option)
		printf("\n");
	g_ret_cmd = 0;
}

// static void	print_echo(char **lex, int option) -> doesn't work for "echo 'one    two'"...
// {
// 	int		index;
// 	int		sub_index;
// 	char	quote;

// 	quote = 0;
// 	index = option;
// 	while (lex[++index])
// 	{
// 		if (index > option + 1)
// 			write(1, " ", 1);
// 		sub_index = -1;
// 		while (lex[index][++sub_index])
// 		{
// 			if (ft_strchr("'\"", lex[index][sub_index]))
// 			{
// 				if (!quote)
// 					quote = lex[index][sub_index];
// 				else if (lex[index][sub_index] == quote)
// 					quote = 0;
// 				else
// 					write(1, &lex[index][sub_index], 1);
// 			}
// 			else
// 				write(1, &lex[index][sub_index], 1);
// 		}
// 	}
// }