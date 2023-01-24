/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greet.c                                            :+:      :+:    :+:   */
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
		free(envp->key);
		free(envp->value);
		tmp = envp;
		envp = envp->next;
		free(tmp);
	}
}

void	close_program(t_ms *ms, char *rl, char **lex, int piping)
{
	(void)rl;
	if (piping)
		return ;
	printf("\n");
	set_col(RED);
	greet_user(ms->envp);
	set_col(WHITE);
	printf("\n");
	free_envp(ms->envp);
	ft_free_arr(lex);
	ft_free_arr(ms->pipes);
	ft_free_arr(ms->semicolons);
	exit(g_ret_cmd);
}

/* any call to this function must be followed by a printf("\n"); */
void	set_col(char *col)
{
	printf("%s", col);
}

void	greet_user(t_envp *envp)
{
	printf("/* ****************************************************************\
********** */\n");
	printf("/*                                                                 \
           */\n");
	printf("/*                                                        :::      \
::::::::   */\n");
	printf("/*   minishell                   shlvl : %-14s :+:      :+:    :+: \
  */\n", ft_getenv(envp, "SHLVL"));
	printf("/*                                                    +:+ +:+      \
   +:+     */\n");
	printf("/*   By: romvan-d && yhuberla                       +#+  +:+       \
+#+        */\n");
	printf("/*                                                +#+#+#+#+#+   +#+\
           */\n");
	printf("/*   Created: 2023/01/10 09:47:48                      #+#    #+#  \
           */\n");
	printf("/*   Updated: 2023/01/18 18:00:52                     ###   #######\
#.fr       */\n");
	printf("/*                                                                 \
           */\n");
	printf("/* ****************************************************************\
********** */\n");
}
