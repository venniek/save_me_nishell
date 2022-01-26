/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:34:17 by naykim            #+#    #+#             */
/*   Updated: 2022/01/26 14:14:05 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	check_alnum_newkey(char *new, char **new_key, int *new_len)
{
	int	i;

	*new_key = ft_substr(new, 0, ft_strchr(new, '=') - new);
	*new_len = ft_strlen(*new_key);
	if (*new_len == 0)
	{
		free(*new_key);
		printf_err("minishell: export: \'");
		printf_err(new);
		return (printf_err("\': not a valid identifier\n"));
	}
	i = -1;
	while (++i < *new_len)
	{
		if (!(ft_isalnum((*new_key)[i]) || (*new_key)[i] == '_'))
		{
			free(*new_key);
			printf_err("minishell: export: \'");
			printf_err(new);
			return (printf_err("\': not a valid identifier\n"));
		}
	}
	return (0);
}

int	ft_export(t_var *var, char *new)
{
	int		i;
	int		new_len;
	char	*new_key;

	if (check_alnum_newkey(new, &new_key, &new_len) == 1)
		return (1);
	i = -1;
	while (++i < (int)ft_sstrlen(var->our_env))
	{
		if (!ft_strncmp(var->our_env[i], new_key, new_len)
			&& (new[new_len] == '\0' || new[new_len] == '='))
		{
			if (new[new_len] == '=')
			{
				free(var->our_env[i]);
				var->our_env[i] = ft_strdup(new);
			}
			free(new_key);
			return (0);
		}
	}
	free(new_key);
	var->our_env = ft_addonestring(var->our_env, new);
	return (0);
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
		else if (sorted_env[idx][ft_strlen(sorted_env[idx]) - 1] == '=')
			printf("=\"\"");
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
			if (ft_strncmp(sorted_env[j], sorted_env[j + 1],
					ft_strlen(sorted_env[j])) > 0)
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

	if (!var || !(var->our_env) || !cmd)
		return ;
	if (cmd[1] == NULL)
		b_export_noarg(var);
	i = 1;
	while (cmd[i])
	{
		if (ft_export(var, cmd[i]) == 1)
			break ;
		i++;
	}
}
