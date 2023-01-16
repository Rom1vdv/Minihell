/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:26:08 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/16 14:42:07 by yhuberla         ###   ########.fr       */
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
	ms->ret_cmd = 0;
	ms->rl = 0;
	ms->envp_original = envp;
	ms->envp = env_init(envp);
	env_increment_shlvl(ms->envp);
	set_col(GREEN);
	greet_user(ms->envp);
	set_col(WHITE);
	printf("\n");
}

static void	ft_catshortdir(char prompt[255])
{
	int		start;
	int		end;
	char	pwd[255];

	if (!getcwd(pwd, sizeof(pwd)))
		return ;
	end = ft_strlen(pwd) - 1;
	start = end;
	while (start > 0 && pwd[start] != '/')
		--start;
	if (pwd[start] == '/')
		++start;
	if (end - start > 19)
	{
		pwd[start + 18] = '\0';
		ft_strcat(pwd, "..");
	}
	ft_strcat(prompt, &pwd[start]);
}

static void	loop(t_ms *ms)
{
	int		loglen;
	char	*rl;
	char	*logname;
	char	prompt[255];

	while (1)
	{
		logname = ft_strdup(ft_getenv(ms->envp, "LOGNAME"));
		if (!logname)
			logname = ft_strdup("anonymous");
		loglen = ft_strlen(logname);
		if (loglen > 20)
		{
			logname[18] = '\0';
			ft_strcat(logname, "..");
		}
		if (!ms->ret_cmd)
		{
			ft_strcpy(prompt, PURPLE);
			ft_strcat(prompt, "○ ");
		}
		else
		{
			ft_strcpy(prompt, RED);
			ft_strcat(prompt, "⦿ ");
			ft_strcat(prompt, PURPLE);
		}
		ft_strcat(prompt, logname);
		free(logname);
		ft_strcat(prompt, WHITE);
		ft_strcat(prompt, " ");
		ft_catshortdir(prompt);
		ft_strcat(prompt, " $> ");
		rl = readline(prompt);
		if (!rl)	// == ctrl+D
			close_program(ms, 0, 0);
		add_history(rl);
		lexer_bonus(rl, ms);
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
