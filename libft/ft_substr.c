/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 19:59:03 by gyeon             #+#    #+#             */
/*   Updated: 2021/05/16 20:29:52 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*pt;
	size_t	len_s;

	if (s == NULL)
		pt = NULL;
	else
	{
		len_s = ft_strlen(s);
		if (len_s < start)
			pt = ft_calloc(1, sizeof(char));
		else
		{
			if (len > len_s - start)
				len = len_s - start;
			pt = (char *)malloc(sizeof(char) * len + 1);
			if (pt != NULL)
				ft_strlcpy(pt, s + start, len + 1);
		}
	}
	return (pt);
}
