/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:31:57 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/23 08:44:44 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/* SIGINT = ctrl+c */
void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
		g_ret_cmd = 1;
	}
	else if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}

void	signal_handler_process(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
		g_ret_cmd = 130;
	}
	else if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		g_ret_cmd = 131;
		return ;
	}
}

void	ft_set_signals(t_ms *ms, int process)
{
	struct termios	term;

	sigemptyset(&ms->act_int.sa_mask);
	sigemptyset(&ms->act_quit.sa_mask);
	if (process)
	{
		ms->act_int.sa_handler = signal_handler_process;
		ms->act_quit.sa_handler = signal_handler_process;
	}
	else
	{
		ms->act_int.sa_handler = signal_handler;
		ms->act_quit.sa_handler = signal_handler;
	}
	if (sigaction(SIGINT, &ms->act_int, NULL) == -1)
		ft_perror("sigaction");
	if (sigaction(SIGQUIT, &ms->act_quit, NULL) == -1)
		ft_perror("sigaction");
	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
}
