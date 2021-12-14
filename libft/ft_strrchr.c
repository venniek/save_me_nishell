/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:18:54 by gyeon             #+#    #+#             */
/*   Updated: 2021/06/01 14:26:03 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	leng;
	char	*result;

	result = NULL;
	leng = ft_strlen(s);
	while (leng)
	{
		if (*(s + leng) == (unsigned char)c)
		{
			result = (char *)s + leng;
			break ;
		}
		leng--;
	}
	if (*s == (unsigned char)c && result == NULL)
		result = (char *)s;
	return (result);
}
