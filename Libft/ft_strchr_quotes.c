/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 08:19:16 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/19 08:26:17 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_quotes(char *str, char c)
{
	size_t	index;
	char	quote;

	if (!str)
		return (0);
	index = 0;
	while (str[index])
	{
		if (ft_strchr("'\"", str[index]))
		{
			quote = str[index++];
			while (str[index] && str[index] != quote)
				++index;
		}
		if (str[index] == c)
			return (&str[index]);
		++index;
	}
	if (str[index] == c)
		return (&str[index]);
	return (0);
}
