/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhuberla <yhuberla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:44:27 by yhuberla          #+#    #+#             */
/*   Updated: 2023/01/12 15:44:34 by yhuberla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
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
		if (res < save)
			return (-(sign == 1));
	}
	return (res * sign);
}
