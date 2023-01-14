/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 09:48:45 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/10 09:48:46 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	size_t	index;

	if (!s)
		return (0);
	index = 0;
	while (s[index])
	{
		if (s[index] == (char) c)
			return ((char *)&s[index]);
		++index;
	}
	if (s[index] == (char) c)
		return ((char *)&s[index]);
	return (0);
}
