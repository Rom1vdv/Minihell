/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:13:39 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/19 08:53:36 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	exec_pwd(void)
{
	char	pwd[255];

	if (getcwd(pwd, sizeof(pwd)))
	{
		printf("%s\n", pwd);
		g_ret_cmd = 0;
	}
	else
		g_ret_cmd = 1;
}
