/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 21:49:24 by gyeon             #+#    #+#             */
/*   Updated: 2021/08/20 14:32:10 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char const *s, size_t n)
{
	char	*pt;
	size_t	index;

	index = 0;
	pt = (char *)malloc(sizeof(char) * (n + 1));
	if (pt != NULL)
	{
		while (index < n)
		{
			*(pt + index) = *(s + index);
			index++;
		}
		*(pt + index) = '\0';
	}
	return (pt);
}

size_t	cnt_row(char const *s, char c)
{
	size_t	cnt_row;
	size_t	index_s;
	size_t	index_st;

	index_s = 0;
	cnt_row = 0;
	while (*(s + index_s))
	{
		while (*(s + index_s) && *(s + index_s) == c)
			index_s++;
		index_st = index_s;
		while (*(s + index_s) && *(s + index_s) != c)
			index_s++;
		if (index_st < index_s)
			cnt_row++;
	}
	return (cnt_row);
}

void	err_free(char **pt, size_t index_row)
{
	size_t	index;

	index = 0;
	while (index < index_row)
		free(*(pt + index));
	free(pt);
	pt = NULL;
}

void	initzero_var(size_t *a, size_t *b, size_t *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

char	**ft_split(char const *s, char c)
{
	size_t	idx_s[2];
	size_t	idx_row;
	char	**pt;

	if (s == NULL)
		return (NULL);
	pt = (char **)malloc(sizeof(char *) * (cnt_row(s, c) + 1));
	initzero_var(&idx_s[0], &idx_s[1], &idx_row);
	while (*(s + idx_s[0]) && pt != NULL)
	{
		while (*(s + idx_s[0]) && *(s + idx_s[0]) == c)
			idx_s[0]++;
		idx_s[1] = idx_s[0];
		while (*(s + idx_s[0]) && *(s + idx_s[0]) != c)
			idx_s[0]++;
		if (idx_s[0] > idx_s[1])
		{
			*(pt + idx_row) = ft_strndup(s + idx_s[1], idx_s[0] - idx_s[1]);
			if (*(pt + idx_row++) == NULL)
				err_free(pt, idx_row - 1);
		}
	}
	if (pt != NULL)
		*(pt + idx_row) = NULL;
	return (pt);
}
