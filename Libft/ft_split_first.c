/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_first.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 09:36:49 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/19 09:56:36 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_get_first_word(char const *s, char c, size_t *ptri)
{
	size_t	len;
	size_t	index;
	char	*res;

	len = 0;
	while (s[*ptri + len] && s[*ptri + len] != c)
		++len;
	++len;
	res = ft_malloc(sizeof(*res) * len, "gfw in split");
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

static char	*ft_get_second_word(char const *s, char c, size_t *ptri)
{
	size_t	len;
	size_t	index;
	char	*res;

	if (s[*ptri] == c)
		++(*ptri);
	len = 0;
	while (s[*ptri + len])
		++len;
	++len;
	res = ft_malloc(sizeof(*res) * len, "gfw in split");
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

char	**ft_split_first(char const *s, char c)
{
	size_t	sindex;
	size_t	mallen;
	char	**res;

	if (!s)
		return (0);
	mallen = 2;
	if (ft_strchr(s, c))
		++mallen;
	res = ft_malloc(sizeof(*res) * mallen, "split_first");
	sindex = 0;
	res[0] = ft_get_first_word(s, c, &sindex);
	if (mallen == 3)
		res[1] = ft_get_second_word(s, c, &sindex);
	res[mallen - 1] = 0;
	return (res);
}
