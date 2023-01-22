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

static int	ft_check_option(char *lex)
{
	int	index;

	if (lex[0] != '-' || lex[1] != 'n')
		return (0);
	index = 2;
	while (lex[index])
	{
		if (lex[index] != 'n')
			return (0);
		++index;
	}
	return (1);
}

void	exec_echo(char **lex)
{
	int		option;
	int		index;

	if (!lex[1])
		return (ft_putendl(""));
	option = ft_check_option(lex[1]);
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
