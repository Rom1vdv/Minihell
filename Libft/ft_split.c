/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 09:48:42 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/10 09:48:42 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_get_mallen(char const *s, char c)
{
	size_t	index;
	size_t	res;

	index = 0;
	res = 0;
	while (s[index])
	{
		while (s[index] == c)
			++index;
		if (s[index] && s[index] != c)
			++res;
		while (s[index] && s[index] != c)
			++index;
	}
	return (res + 1);
}

static char	*ft_get_next_word(char const *s, char c, size_t *ptri)
{
	size_t	len;
	size_t	index;
	char	*res;

	while (s[*ptri] == c)
		(*ptri)++;
	len = 0;
	while (s[*ptri + len] && s[*ptri + len] != c)
		++len;
	++len;
	res = malloc(sizeof(*res) * len);
	if (!res)
		return (0);
	index = 0;
	while (index < len - 1)
	{
		res[index] = s[*ptri];
		++index;
		++(*ptri);
	}
	res[index] = '\0';
	return (res);
}

static char	**ft_free_return(char **res, size_t limit)
{
	size_t	index;

	index = 0;
	while (index < limit)
		free(res[index++]);
	free(res);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	index;
	size_t	sindex;
	size_t	mallen;
	char	**res;

	if (!s)
		return (0);
	mallen = ft_get_mallen(s, c);
	res = malloc(sizeof(*res) * mallen);
	if (!res)
		return (0);
	index = 0;
	sindex = 0;
	while (index < mallen - 1)
	{
		res[index] = ft_get_next_word(s, c, &sindex);
		if (!res[index])
			return (ft_free_return(res, index));
		++index;
	}
	res[index] = 0;
	return (res);
}
