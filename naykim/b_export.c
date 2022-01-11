/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayeon <nayeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:09:13 by naykim            #+#    #+#             */
/*   Updated: 2022/01/11 17:54:29 by nayeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	**ft_export(char **env, char *new)
{
	int		i;
	char	**split_new;
	char	**tmp_env;

	if (!env || !new)
		return ;
	tmp_env = env;
	if (!ft_strrchr(new, '='))
		return ;
	split_new = ft_split(new, '=');
	i = -1;
	while (++i < ft_sstrlen(tmp_env))
	{
		if (!ft_strncmp(tmp_env[i], split_new[0], ft_strlen(split_new[0])))
		{
			free(tmp_env[i]);
			tmp_env[i] = ft_strdup(new);
			return ;
		}
	}
	*env = ft_addonestring(tmp_env, new);
}

void	b_export(char ***our_env, char **cmd)
{
	int	i;

	i = 1;
	while (i < ft_sstrlen(cmd))
	{
		*our_env = ft_export(*our_env, cmd[i]);
		i++;
	}
}
