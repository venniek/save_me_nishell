/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:17:45 by gyeon             #+#    #+#             */
/*   Updated: 2021/08/20 14:14:50 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	short	flg;
	size_t	leng_dst;
	size_t	leng_src;
	size_t	index_src;

	flg = 0;
	leng_dst = 0;
	index_src = 0;
	leng_src = ft_strlen(src);
	while (*(dst + leng_dst))
	{
		if (leng_dst++ == dstsize)
		{
			--leng_dst;
			flg = 1;
			break ;
		}
	}
	if (flg == 0)
	{
		while (*(src + index_src) != '\0' && index_src + leng_dst + 1 < dstsize)
			*(dst++ + leng_dst) = *(src + index_src++);
		*(dst + leng_dst) = '\0';
	}
	return (leng_dst + leng_src);
}
