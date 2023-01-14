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

#include "../Includes/minishell.h"

static void	free_envp(t_envp *envp)
{
	t_envp	*tmp;

	while (envp)
	{
		printf("freeing %s=%s\n", envp->key, envp->value);
		free(envp->key);
		free(envp->value);
		tmp = envp;
		envp = envp->next;
		free(tmp);
	}
}

void	close_program(t_envp *envp, char *rl)
{
	free(rl);
	printf("\n");
	set_col(RED);
	greet_user(envp);
	set_col(WHITE);
	printf("\n");
	free_envp(envp);
	exit(EXIT_SUCCESS);
}

/* any call to this function must be followed by a printf("\n"); */
void	set_col(char *col)
{
	printf("%s", col);
}

void	greet_user(t_envp *envp)
{
	printf("/* ************************************************************************** */\n");
	printf("/*                                                                            */\n");
	printf("/*                                                        :::      ::::::::   */\n");
	printf("/*   minishell               shlvl : %-18s :+:      :+:    :+:   */\n", ft_getenv(envp, "SHLVL"));
	printf("/*                                                    +:+ +:+         +:+     */\n");
	printf("/*   By: romvan-d && yhuberla                       +#+  +:+       +#+        */\n");
	printf("/*                                                +#+#+#+#+#+   +#+           */\n");
	printf("/*   Created: 2023/01/10 09:47:48 by authors           #+#    #+#             */\n");
	printf("/*   Updated: 2023/01/13 09:39:06 by authors          ###   ########.fr       */\n");
	printf("/*                                                                            */\n");
	printf("/* ************************************************************************** */\n");
}
