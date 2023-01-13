/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:13:39 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/13 10:48:40 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	exec_pwd(int *ret_cmd)
{
	char	pwd[255];

	if (getcwd(pwd, sizeof(pwd)))
	{
		printf("%s\n", pwd);
		*ret_cmd = 0;
	}
	else
		*ret_cmd = 1;
}
