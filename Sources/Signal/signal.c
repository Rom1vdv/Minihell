/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:31:57 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/17 14:14:51 by yhuberla         ###   ########.fr       */
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
		// rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}
