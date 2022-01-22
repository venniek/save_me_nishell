/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naykim <naykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 22:21:41 by gyeon             #+#    #+#             */
/*   Updated: 2022/01/22 16:27:40 by naykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	over_range(int sign)
{
	if (sign == 1)
		return (2147483647);
	else
		return (-2147483648);
}

long long	ft_atoi(const char *str)
{
	long long	atoi;
	int			i;
	int			sign;

	i = 0;
	sign = 1;
	atoi = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		atoi = atoi * 10 + str[i] - '0';
		i++;
	}
	if (atoi > 2147483647)
		return (over_range(sign));
	return (atoi * sign);
}

