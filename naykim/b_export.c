/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayeon <nayeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:09:13 by naykim            #+#    #+#             */
/*   Updated: 2022/01/12 02:59:17 by nayeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	**ft_sstrdup(char **origin)
{
	int		i;
	int		env_len;
	char	**new_env;

	if (!origin)
		return (NULL);
	env_len = ft_sstrlen(origin);
	new_env = (char **)malloc(sizeof(char *) * (env_len + 1));
	i = -1;
	while (++i < env_len)
		new_env[i] = ft_strdup(origin[i]);
	new_env[i] = NULL;
	return (new_env);
}

char	**ft_export(char **env, char *new)
{
	int		i;
	char	*new_key;
	char	**new_env;

	if (!env || !new)
		return ;
	new_env = ft_sstrdup(env);
	if (!ft_strrchr(new, '='))
		return (env);
	free(env);
	new_key = ft_substr(new, 0, ft_strchr(new, '=') - new);
	i = -1;
	while (++i < ft_sstrlen(new_env))
	{
		if (!ft_strncmp(new_env[i], new_key, ft_strlen(new_key)))
		{
			free(new_env[i]);
			new_env[i] = ft_strdup(new);
			return (new_env);
		}
	}
	new_env = ft_addonestring(new_env, new);
	return (new_env);
}

void	b_export(char ***our_env, char **cmd)
{
	int		i;
	char	**new_env;

	if (!(*our_env) || !cmd)
		return (NULL);
	new_env = ft_sstrdup(*our_env);
	i = 1;
	while (i < ft_sstrlen(cmd))
	{
		new_env = ft_export(new_env, cmd[i]);
		i++;
	}
	free(*our_env);
	*our_env = new_env;
}
