/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:28:18 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/16 10:28:18 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_mallen(char *str, char c)
{
	size_t	index;
	size_t	res;
	char	quote;

	index = 0;
	res = 0;
	while (str[index])
	{
		while (str[index] == c)
			++index;
		if (str[index] && str[index] != c)
			++res;
		while (str[index] && str[index] != c)
		{
			if (ft_strchr("'\"", str[index]))
			{
				quote = str[index++];
				while (str[index] && str[index] != quote)
					++index;
			}
			++index;
		}
	}
	return (res + 1);
}

static char	*ft_get_next_word(char *str, char c, size_t *ptri)
{
	size_t	len;
	size_t	index;
	char	*res;
	char	quote;

	while (str[*ptri] == c)
		(*ptri)++;
	len = 0;
	while (str[*ptri + len] && str[*ptri + len] != c)
	{
		if (ft_strchr("'\"", str[*ptri + len]))
		{
			quote = str[*ptri + (len++)];
			while (str[*ptri + len] && str[*ptri + len] != quote)
				++len;
		}
		++len;
	}
	res = ft_malloc(sizeof(*res) * (len + 1), "gnw in split quotes");
	index = -1;
	while (++index < len)
		res[index] = str[(*ptri)++];
	res[index] = '\0';
	return (res);
}

char	**ft_split_quotes(char *str, char c)
{
	size_t	index;
	size_t	sindex;
	size_t	mallen;
	char	**res;

	if (!str)
		return (0);
	mallen = ft_get_mallen(str, c);
	res = ft_malloc(sizeof(*res) * mallen, "split quotes");
	index = 0;
	sindex = 0;
	while (index < mallen - 1)
	{
		res[index] = ft_get_next_word(str, c, &sindex);
		++index;
	}
	res[index] = 0;
	return (res);
}
