/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:34:17 by naykim            #+#    #+#             */
/*   Updated: 2022/01/25 13:16:38 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_export(t_var *var, char *new)
{
	int		i;
	char	*new_key;

	if (!var->our_env || !new)
		return ;
	new_key = ft_substr(new, 0, ft_strchr(new, '=') - new);
	i = -1;
	while (++i < (int)ft_sstrlen(var->our_env))
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

void	b_export_noarg(t_var *var)
{
	size_t	idx;

	idx = 0;
	while (var->our_env[idx] != NULL)
		printf("declare -x %s\n", var->our_env[idx++]);
}

void	b_export(t_var *var, char **cmd)
{
	int		i;

	if (!(var->our_env) || !cmd)
		return ;
	if (cmd[1] == NULL)
		b_export_noarg(var);
	i = 1;
	while (i < (int)ft_sstrlen(cmd))
	{
		ft_export(var, cmd[i]);
		i++;
	}
}
