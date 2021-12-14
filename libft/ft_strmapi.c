/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 23:42:45 by gyeon             #+#    #+#             */
/*   Updated: 2021/05/16 19:49:30 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	index;
	char	*pt;

	index = 0;
	pt = NULL;
	if (s != NULL && f != NULL)
	{
		len = ft_strlen(s);
		pt = (char *)malloc(sizeof(char) * len + 1);
		if (pt != NULL)
		{
			while (index < len)
			{
				*(pt + index) = f(index, *(s + index));
				index++;
			}
			*(pt + index) = '\0';
		}
	}
	return (pt);
}
