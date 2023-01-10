/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:54:52 by yhuberla          #+#    #+#             */
/*   Updated: 2022/11/28 14:26:07 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_mallen(int ac, va_list ap)
{
	int	index;
	int	res;

	res = 0;
	index = 0;
	while (index < ac)
	{
		res += ft_strlen(va_arg(ap, char *));
		++index;
	}
	return (res);
}

static void	ft_gnw(va_list *ap, char *res, int *index)
{
	char	*tmp;
	int		len;
	int		sub_index;

	tmp = va_arg(*ap, char *);
	len = ft_strlen(tmp);
	sub_index = 0;
	while (sub_index < len)
	{
		res[*index] = tmp[sub_index];
		++sub_index;
		++(*index);
	}
}

char	*ft_strjoins(int ac, ...)
{
	int		wc;
	int		index;
	va_list	ap;
	va_list	ap_cpy;
	char	*res;

	va_start(ap, ac);
	va_copy(ap_cpy, ap);
	res = malloc(sizeof(*res) * (ft_mallen(ac, ap_cpy) + 1));
	if (!res)
		return (0);
	index = 0;
	wc = -1;
	while (++wc < ac)
		ft_gnw(&ap, res, &index);
	res[index] = 0;
	va_end(ap);
	return (res);
}
