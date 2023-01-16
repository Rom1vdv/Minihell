/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:27:02 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/16 10:27:02 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	*ft_malloc(int size, char *msg)
{
	void	*res;

	res = malloc(size);
	if (!res)
		ft_perror(msg);
	return (res);
}
