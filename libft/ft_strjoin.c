/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:41:24 by gyeon             #+#    #+#             */
/*   Updated: 2021/05/15 16:29:55 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*pt;
	size_t	len_s1;
	size_t	len_s2;

	if (s1 == NULL && s2 == NULL)
		pt = NULL;
	else if (s1 == NULL)
		pt = ft_strdup(s2);
	else if (s2 == NULL)
		pt = ft_strdup(s1);
	else
	{
		len_s1 = ft_strlen(s1);
		len_s2 = ft_strlen(s2);
		pt = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
		if (pt != NULL)
		{
			ft_strlcpy(pt, s1, len_s1 + 1);
			ft_strlcat(pt, s2, len_s1 + len_s2 + 1);
		}
	}
	return (pt);
}
