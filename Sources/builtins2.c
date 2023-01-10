/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:02:28 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/10 18:27:30 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_env(t_envp *envp)
{
	while (envp)
	{
		printf("%s=%s\n", envp->head, envp->value);
		envp = envp->next;
	}
}
