/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:26:08 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/10 20:45:25 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

/* SIGINT = CTRL+C, */
static void	setup(t_ms *ms, char **envp)
{
	struct sigaction act;

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &signal_handler;
	if (sigaction(SIGINT, &act, NULL) == -1)
		ft_perror("sigaction");
	ms->envp_original = envp;
	ms->envp = env_init(envp);
	set_col(GREEN);
	greet_user();
	set_col(WHITE);
	printf("\n");
}

static void	loop(t_ms *ms)
{
	char	*rl;
	char	*logname;
	char	*pwd;

	while (1)
	{
		logname = ft_getenv(ms->envp, "LOGNAME");
		write(1, logname, ft_strlen(logname));
		write(1, " ", 1);
		pwd = ft_getenv(ms->envp, "PWD");
		write(1, pwd, ft_strlen(pwd));
		rl = readline(" $> ");
		if (!rl)	// == ctrl+D
			close_program();
		add_history(rl);
		lexer(rl, ms);
		free(rl);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_ms	ms;

	(void)ac;
	(void)av;
	if (ac == 1)
	{
		setup(&ms, envp);
		loop(&ms);
	}
	else
	{
		printf("I identify as a argument-less executable, please refer to me as such.\n");
		return (1);
	}
	return (0);
}
