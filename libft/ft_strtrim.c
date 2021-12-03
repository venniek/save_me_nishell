/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 11:40:04 by gyeon             #+#    #+#             */
/*   Updated: 2021/08/20 14:36:05 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	find_lastindex(char const *s)
{
	size_t	len;

	len = 0;
	while (*(s + len))
		len++;
	if (len == 0)
		return (0);
	else
		return (len - 1);
}

size_t	trimable_front(char const *s, char const *set)
{
	size_t	cnt_front;

	cnt_front = 0;
	while (*(s + cnt_front))
	{
		if (ft_strchr(set, *(s + cnt_front)) != NULL)
			cnt_front++;
		else
			break ;
	}
	return (cnt_front);
}

size_t	trimable_rear(char const *s, char const *set)
{
	size_t	cnt_rear;
	size_t	len;

	cnt_rear = 0;
	len = ft_strlen(s);
	while (cnt_rear < len)
	{
		if (ft_strchr(set, *(s + len - 1 - cnt_rear)) != NULL)
			cnt_rear++;
		else
			break ;
	}
	return (cnt_rear);
}

/*
** flg_fr[0] : flag of front
** flg_fr[1] : flag of rear
** index_sf[0] : starting index of s to copy
** index_sf[1] : finishing index of s to copy
*/

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	flg_fr[2];
	size_t	i_last;
	char	*pt;

	if (s1 == NULL)
		pt = NULL;
	else if (set == NULL)
		pt = ft_strdup(s1);
	else
	{
		i_last = find_lastindex(s1);
		flg_fr[0] = trimable_front(s1, set);
		flg_fr[1] = trimable_rear(s1, set);
		if (flg_fr[0] + flg_fr[1] < i_last + 1)
		{
			pt = (char *)malloc(sizeof(char)
					* (i_last + 2 - flg_fr[0] - flg_fr[1]));
			if (pt != NULL)
				ft_strlcpy(pt, s1 + flg_fr[0],
					i_last + 2 - flg_fr[0] - flg_fr[1]);
		}
		else
			pt = ft_strdup("\0");
	}
	return (pt);
}
