/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_set.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romvan-d <romvan-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:21:35 by romvan-d          #+#    #+#             */
/*   Updated: 2023/01/24 17:35:40 by romvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_mallen(char const *s, char *set)
{
	size_t	index;
	size_t	res;
	char	quote;

	index = 0;
	res = 0;
	while (s[index])
	{
		while (s[index] && ft_strchr(set, s[index]))
			++index;
		if (s[index] && !ft_strchr(set, s[index]))
			++res;
		while (s[index] && !ft_strchr(set, s[index]))
		{
			if (ft_strchr("'\"", s[index]))
			{
				quote = s[index++];
				while (s[index] && s[index] != quote)
					++index;
			}
			++index;
		}
	}
	return (res + 1);
}

static char	*ft_get_next_word(char const *s, char *set, size_t *ptri)
{
	size_t	len;
	size_t	index;
	char	*res;
	char	quote;

	while (s[*ptri] && ft_strchr(set, s[*ptri]))
		++(*ptri);
	len = 0;
	while (s[*ptri + len] && !ft_strchr(set, s[*ptri + len]))
	{
		if (ft_strchr("'\"", s[*ptri + len]))
		{
			quote = s[*ptri + (len++)];
			while (s[*ptri + len] && s[*ptri + len] != quote)
				++len;
		}
		++len;
	}
	++len;
	res = ft_malloc(sizeof(*res) * len, "gnw in split_set");
	index = -1;
	while (++index < len - 1)
		res[index] = s[(*ptri)++];
	res[index] = '\0';
	return (res);
}

char	**ft_split_quotes_set(char const *s, char *set)
{
	size_t	index;
	size_t	sindex;
	size_t	mallen;
	char	**res;

	if (!s)
		return (0);
	mallen = ft_get_mallen(s, set);
	res = ft_malloc(sizeof(*res) * mallen, "split_set");
	index = 0;
	sindex = 0;
	while (index < mallen - 1)
	{
		res[index] = ft_get_next_word(s, set, &sindex);
		++index;
	}
	res[index] = 0;
	return (res);
}
