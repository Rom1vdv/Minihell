/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 09:47:43 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/10 09:47:43 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static void	print_echo(char *str)
{
	int		index;
	char	quote;

	index = 0;
	quote = 0;
	while (str[++index])
	{
		if (ft_strchr("'\"", str[index]))
		{
			if (!quote)
				quote = str[index];
			else if (str[index] == quote)
				quote = 0;
			else
				write(1, &str[index], 1);
		}
		else if (quote || str[index] != ' ')
			write(1, &str[index], 1);
		else if (str[index - 1] != ' ')
			write(1, " ", 1);
	}
}

/**
 * It prints the arguments passed to it, with the option to not print a newline at the end
 * 
 * @param lex array of strings, each string is a word in the command line
 * @param args "-n hello world"
 */
void	exec_echo(char **lex, char *args)
{
	int		option;

	if (ft_arraylen(lex) == 1)
		return (ft_putendl(""));
	option = (!ft_strncmp(lex[1], "-n", 3));
	if (option)
		args = ft_strchr(args, 'n') + 1;
	if (check_quotes(args))
		printf("Unclosed quotes detected, pls fix");
	else
		print_echo(args);
	if (!option)
		printf("\n");
}

/**
 * It gets the current working directory and prints it to the standard output
 */
void	display_pwd(void)
{
	char	str[255];

	if (getcwd(str, sizeof(str)))
			printf("%s\n", str);
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