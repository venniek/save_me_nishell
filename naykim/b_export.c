/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naykim <naykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:34:17 by naykim            #+#    #+#             */
/*   Updated: 2022/01/13 16:34:20 by naykim           ###   ########.fr       */
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

void	ft_export(t_var *var, char *new)
{
	int		i;
	char	*new_key;

	if (!var->our_env || !new)
		return ;
	if (!ft_strrchr(new, '='))
		return ;
	new_key = ft_substr(new, 0, ft_strchr(new, '=') - new);
	i = -1;
	while (++i < ft_sstrlen(var->our_env))
	{
		if (!ft_strncmp(var->our_env[i], new_key, ft_strlen(new_key)))
		{
			free(var->our_env[i]);
			var->our_env[i] = ft_strdup(new);
			free(new_key);
			return ;
		}
	}
	free(new_key);
	var->our_env = ft_addonestring(var->our_env, new);
}

void	b_export(t_var *var, char **cmd)
{
	int		i;

	if (!(var->our_env) || !cmd)
		return ;
	i = 1;
	while (i < ft_sstrlen(cmd))
	{
		ft_export(var, cmd[i]);
		i++;
	}
}
