/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:26:08 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/19 08:55:58 by yhuberla         ###   ########.fr       */
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
	g_ret_cmd = 0;
	ms->rl = 0;
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
		if (!g_ret_cmd)
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
			close_program(ms, 0, 0, 0);
		add_history(rl);
		lexer_bonus(rl, ms);
		free(rl);
	}
}

static int	ft_launch_minishell(char *av, char **envp)
{
	t_ms	ms;
	
	setup(&ms, envp);
	lexer_bonus(av, &ms);
	return (g_ret_cmd);
}

int	main(int ac, char **av, char **envp)
{
	t_ms	ms;

	(void)ac;
	(void)av;
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
  	{
    	int exit_status = ft_launch_minishell(av[2], envp);
    	exit(exit_status);
 	}
	if (ac == 1)
	{
		// close(1); //use this to check errors are printed on stderr and not stdout
		setup(&ms, envp);
		loop(&ms);
	}
	else
	{
		write(2, "I identify as a argument-less executable, please refer to me as such.\n", 70);
		return (1);
	}
	return (0);
}
