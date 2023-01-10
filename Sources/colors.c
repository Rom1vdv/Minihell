/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 09:47:48 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/10 09:47:48 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* any call to this function must be followed by a printf("\n"); */
void	set_col(char *col)
{
	printf("%s", col);
}

void	greet_user(void)
{
	printf("/* ************************************************************************** */\n");
	printf("/*                                                                            */\n");
	printf("/*                                                        :::      ::::::::   */\n");
	printf("/*   minishell                                          :+:      :+:    :+:   */\n");
	printf("/*                                                    +:+ +:+         +:+     */\n");
	printf("/*   By: romvan-d && yhuberla                       +#+  +:+       +#+        */\n");
	printf("/*                                                +#+#+#+#+#+   +#+           */\n");
	printf("/*   Created: 2023/01/10 09:47:48 by authors           #+#    #+#             */\n");
	printf("/*   Updated: 2023/01/10 09:47:48 by authors          ###   ########.fr       */\n");
	printf("/*                                                                            */\n");
	printf("/* ************************************************************************** */\n");
}

void	close_program(void)
{
	printf("\n");
	set_col(RED);
	greet_user();
	set_col(WHITE);
	printf("\n");
	exit(EXIT_SUCCESS);
}
