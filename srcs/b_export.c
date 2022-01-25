/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naykim <naykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:34:17 by naykim            #+#    #+#             */
/*   Updated: 2022/01/25 20:11:56 by naykim           ###   ########.fr       */
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

void	print_sorted_env(char **sorted_env)
{
	char	**tmpsstr;
	int		idx;

	idx = 0;
	while (sorted_env[idx] != NULL)
	{
		tmpsstr = ft_split(sorted_env[idx], '=');
		printf("declare -x %s", tmpsstr[0]);
		if (tmpsstr[1])
			printf("=\"%s\"", tmpsstr[1]);
		printf("\n");
		free_sstr(tmpsstr);
		idx++;
	}
	free_sstr(sorted_env);
}

void	b_export_noarg(t_var *var)
{
	int		i;
	int		j;
	char	**sorted_env;
	char	*tmp;
	
	sorted_env = ft_sstrdup(var->our_env);
	i = -1;
	while (++i < (int)ft_sstrlen(sorted_env) - 1)
	{
		j = 0;
		while (i + j < (int)ft_sstrlen(sorted_env) - 1)
		{
			if (ft_strncmp(sorted_env[j], sorted_env[j + 1], ft_strlen(sorted_env[j])) > 0)
			{
				tmp = sorted_env[j];
				sorted_env[j] = sorted_env[j + 1];
				sorted_env[j + 1] = tmp;
			}
			j++;
		}
	}
	print_sorted_env(sorted_env);
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
