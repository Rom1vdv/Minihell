/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 08:42:48 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/23 08:42:48 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

/* error messages are formated as follow :            *
*  -minishell: <cmd>: error message                   *
*  this function reduces nbr of lines other functions */
void	ft_stderr(char *str, char *str1, char *str2)
{
	write(2, str, ft_strlen(str));
	write(2, str1, ft_strlen(str1));
	write(2, str2, ft_strlen(str2));
	g_ret_cmd = 1;
}

void	env_increment_shlvl(t_envp *envp)
{
	int		shlvl;
	char	*value;
	char	*new_value;

	value = ft_getenv(envp, "SHLVL");
	if (!value)
		return (ft_setenv(envp, "SHLVL", "1", 1));
	shlvl = ft_atoi(value);
	if (shlvl < 0)
		shlvl = -1;
	new_value = ft_itoa(shlvl + 1);
	ft_setenv(envp, "SHLVL", new_value, 1);
	free(new_value);
}
