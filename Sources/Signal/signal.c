/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romvan-d <romvan-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:31:57 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/19 15:35:13 by romvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/* SIGINT = ctrl+c */
void	signal_handler(int signo, siginfo_t *info, void *context)
{
	(void)context;
	(void)signo;
	(void)info;
	if (signo == SIGINT) // +set cmd_ret to 130 -> is this the allowed global ?
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
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
