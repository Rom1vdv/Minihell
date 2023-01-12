/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:51:01 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/12 15:51:03 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_get_mallen_itoa(int n)
{
	size_t	res;

	res = 2 + (n < 0);
	while (n / 10)
	{
		res ++;
		n /= 10;
	}
	return (res);
}

static void	ft_fill_itoa(char *str, long n, int index)
{
	if (n / 10)
		ft_fill_itoa(str, n / 10, index - 1);
	str[index] = n % 10 + '0';
}

char	*ft_itoa(int n)
{
	char	*res;
	size_t	mallen;

	mallen = ft_get_mallen_itoa(n);
	res = malloc(sizeof(*res) * mallen);
	if (!res)
		return (0);
	if (n < 0)
	{
		res[0] = '-';
		ft_fill_itoa(res, -(long) n, mallen - 2);
	}
	else
		ft_fill_itoa(res, n, mallen - 2);
	res[mallen - 1] = '\0';
	return (res);
}
