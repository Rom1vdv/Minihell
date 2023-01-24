/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:26:08 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/21 20:36:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

/* SIGINT = CTRL+C, */
static void	setup(t_ms *ms, char **envp)
{
	g_ret_cmd = 0;
	ms->rl = 0;
	ms->envp = env_init(envp);
	ms->pids = 0;
	ms->last_pid = 0;
	ms->pipes = 0;
	ms->semicolons = 0;
	env_increment_shlvl(ms->envp);
	set_col(GREEN);
	greet_user(ms->envp);
	set_col(WHITE);
	printf("\n");
}

static void	ft_catlogname(char prompt[255], char *env_logname)
{
	int		loglen;
	char	*logname;

	logname = ft_strdup(env_logname);
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
	if (pwd[start] == '/' && end > 0)
		++start;
	if (end - start > 19)
	{
		pwd[start + 18] = '\0';
		ft_strcat(pwd, "..");
	}
	ft_strcat(prompt, &pwd[start]);
}

/* 	!rl happens when ctrl+D is pressed        *
*   !rl[0] happens when input is only newline */
static void	loop(t_ms *ms)
{
	char	*rl;
	char	prompt[255];

	while (1)
	{
		ft_catlogname(prompt, ft_getenv(ms->envp, "LOGNAME"));
		ft_strcat(prompt, WHITE);
		ft_strcat(prompt, " ");
		ft_catshortdir(prompt);
		ft_strcat(prompt, " $> ");
		ft_set_signals(0);
		ms->pipes = 0;
		ms->semicolons = 0;
		rl = readline(prompt);
		if (!rl)
			close_program(ms, 0, 0, 0);
		if (rl[0])
		{
			add_history(rl);
			prelexer(rl, ms);
		}
		free(rl);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_ms	ms;

	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
	{
		setup(&ms, envp);
		prelexer(av[2], &ms);
		return (g_ret_cmd);
	}
	if (ac == 1)
	{
		setup(&ms, envp);
		loop(&ms);
	}
	else
	{
		write(2, "Usage : './minishell'\n", 22);
		return (1);
	}
	return (0);
}
