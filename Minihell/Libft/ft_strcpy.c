/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:08:53 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/10 17:49:12 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strcpy(char *dst, const char *src)
{
	size_t	index;

	if (!dst)
		return ;
	if (!src)
	{
		dst[0] = '\0';
		return ;
	}
	index = 0;
	while (src[index])
	{
		dst[index] = src[index];
		++index;
	}
	dst[index] = '\0';
}
