/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naykim <naykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:09:40 by naykim            #+#    #+#             */
/*   Updated: 2022/01/06 16:56:12 by naykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int find_remove_str(char **origin, char *remove, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (!ft_strncmp(origin[i], remove, ft_strlen(remove)))
			return (i);
		i++;
	}
	return (-1);
}

char **b_unset(char **origin, char *remove)
{
	char	**new;
	int		idxlen;
	int		i;
	int		newi;
	int		flag;

	if (!origin || !remove)
		return (NULL);
	idxlen = ft_sstrlen(origin);
	flag = find_remove_str(origin, remove, idxlen);
	if (flag != -1)
		new = (char **)malloc(sizeof(char *) * (idxlen + 1));
	else
		return (origin);
	i = -1;
	newi = 0;
	while (++i < idxlen)
	{
		if (i != flag)
			new[newi++] = ft_strdup(origin[i]);
	}
	new[idxlen] = 0;
	i = -1;	
	while (++i < idxlen)
		free(origin[i]);
	free(origin);
	origin = 0;
	return (new);
}
