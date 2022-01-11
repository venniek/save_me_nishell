/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayeon <nayeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:55:37 by nayeon            #+#    #+#             */
/*   Updated: 2022/01/11 17:55:38 by nayeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	find_remove_str(char **origin, char *remove, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (!ft_strncmp(origin[i], remove, ft_strlen(remove)))
			return (i);
		i++;
	}
	return (-1);
}

static char	**ft_removeonestring(char **origin, char *remove)
{
	char	**new;
	int		origin_len;
	int		i;
	int		newi;
	int		flag;

	origin_len = ft_sstrlen(origin);
	flag = find_remove_str(origin, remove, origin_len);
	if (flag != -1)
		new = (char **)malloc(sizeof(char *) * (origin_len));
	else
		return (origin);
	i = -1;
	newi = 0;
	while (++i < origin_len)
	{
		if (i != flag)
			new[newi++] = ft_strdup(origin[i]);
	}
	new[newi] = 0;
	i = -1;
	while (++i < origin_len)
		free(origin[i]);
	free(origin);
	return (new);
}

void	b_unset(char ***our_env, char **cmd)
{
	int	i;

	if (!(*our_env) || !cmd)
		return (NULL);
	i = 1;
	while (i < ft_sstrlen(cmd))
	{
		*our_env = ft_removeonestring(*our_env, cmd[i]);
		i++;
	}
}
