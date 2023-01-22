/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_64bits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:11:36 by romvan-d          #+#    #+#             */
/*   Updated: 2023/01/22 16:17:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_64bits(char *str)
{
	int		index;
	int		sign;
	long	res;
	long	save;

	index = 0;
	sign = 1;
	res = 0;
	while (str[index] == ' ' || (str[index] >= '\t' && str[index] <= '\r'))
		index ++;
	if (str[index] == '+' || str[index] == '-')
	{
		if (str[index ++] == '-')
			sign *= -1;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		save = res;
		res = res * 10 + str[index ++] - '0';
		if (res - (sign == -1) < save)
			return (256);
	}
	return ((char)(res * sign));
}
