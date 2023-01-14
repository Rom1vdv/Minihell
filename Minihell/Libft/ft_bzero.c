/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 09:48:26 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/10 09:48:27 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	index;
	char	*ptrs;

	if (!s)
		return ;
	ptrs = s;
	index = 0;
	while (index < n)
	{
		ptrs[index] = 0;
		index ++;
	}
}
