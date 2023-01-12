/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:26:08 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/12 15:37:01 by yhuberla         ###   ########.fr       */
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
	if (sigaction(SIGQUIT, &act, NULL) == -1)
		ft_perror("sigaction");
	ms->envp_original = envp;
	ms->envp = env_init(envp);
	env_increment_shlvl(ms->envp);
	set_col(GREEN);
	greet_user();
	set_col(WHITE);
	printf("\n");
}

static void	ft_catshortdir(char prompt[255])
{
	int		index;
	char	pwd[255];

	if (!getcwd(pwd, sizeof(pwd)))
		return ;
	index = ft_strlen(pwd) - 1;
	while (index > 0 && pwd[index] != '/')
		--index;
	if (pwd[index] == '/')
		++index;
	ft_strcat(prompt, &pwd[index]);
}

static void	loop(t_ms *ms)
{
	char	*rl;
	char	*logname;
	char	prompt[255];

	while (1)
	{
		logname = ft_getenv(ms->envp, "LOGNAME");
		if (!logname)
			logname = "anonymous";
		ft_strcpy(prompt, PURPLE);
		ft_strcat(prompt, logname);
		ft_strcat(prompt, WHITE);
		ft_strcat(prompt, " ");
		ft_catshortdir(prompt);
		ft_strcat(prompt, " $> ");
		rl = readline(prompt);
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
