/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:11:50 by gyeon             #+#    #+#             */
/*   Updated: 2021/06/01 14:23:03 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (dst != NULL || src != NULL)
	{
		if (dst < src && len != 0)
		{
			i = 0;
			while (i < len)
			{
				*((unsigned char *)dst + i) = *((unsigned char *)src + i);
				i++;
			}
		}
		else if (dst > src && len != 0)
		{
			i = len;
			while (i-- > 0)
				*((unsigned char *)dst + i) = *((unsigned char *)src + i);
		}
	}
	return (dst);
}
