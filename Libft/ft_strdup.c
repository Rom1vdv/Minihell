/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 18:43:21 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/10 18:43:37 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	s1len;
	size_t	index;
	char	*res;

	if (!s1)
		return (0);
	s1len = ft_strlen(s1);
	res = malloc(sizeof(*res) * (s1len + 1));
	if (!res)
		return (0);
	index = 0;
	while (index < s1len + 1)
	{
		res[index] = s1[index];
		index ++;
	}
	return (res);
}
