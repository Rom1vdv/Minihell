/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 09:48:48 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/14 12:24:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	s1len;
	size_t	s2len;
	size_t	index;
	size_t	sub_index;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	res = ft_malloc(sizeof(*res) * (s1len + s2len + 1), "strjoin");
	index = 0;
	while (index < s1len)
	{
		res[index] = s1[index];
		index ++;
	}
	sub_index = 0;
	while (sub_index < s2len)
		res[index ++] = s2[sub_index ++];
	res[index] = '\0';
	return (res);
}
