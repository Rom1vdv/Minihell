/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:55:46 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/11 19:14:35 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strcat(char *dst, const char *src)
{
	size_t	index;
	size_t	dstlen;

	if (!dst || !src)
		return ;
	dstlen = ft_strlen(dst);
	index = 0;
	while (src[index])
	{
		dst[dstlen + index] = src[index];
		++index;
	}
	dst[dstlen + index] = '\0';
}
