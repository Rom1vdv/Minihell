/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:35:24 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/10 19:51:57 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_export(t_ms *ms, char *line)
{
	char	*value;

	if (!line)
	{
		printf("TODO -> printf bunch of stuff when export used alone\n"); //todo
		return ;
	}
	value = ft_strchr(line, '=') + 1;
	if (!value)
		return ;
	line[ft_strlen(line) - ft_strlen(value) - 1] = '\0';
	ft_setenv(ms->envp, line, value);
}
