/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:34:22 by naykim            #+#    #+#             */
/*   Updated: 2022/01/26 15:13:01 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

extern int	g_exitcode;

int	find_remove_str(char **origin, char *remove, int len)
{
	int		i;
	int		r_len;

	r_len = (int)ft_strlen(remove);
	i = 0;
	while (i < len)
	{
		if (!ft_strncmp(origin[i], remove, r_len)
			&& (origin[i][r_len] == '\0' || origin[i][r_len] == '='))
			return (i);
		i++;
	}
	return (-1);
}

char	**ft_removeonestring(char **origin, char *remove, int origin_len)
{
	char	**new;
	int		i;
	int		newi;
	int		flag;

	flag = find_remove_str(origin, remove, origin_len);
	if (flag != -1)
		new = (char **)excep_malloc(sizeof(char *) * (origin_len));
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
	free_sstr(origin);
	return (new);
}

int	check_alnum_remove(char *remove)
{
	int	i;

	i = -1;
	while (++i < (int)ft_strlen(remove))
	{
		if (!(ft_isalnum(remove[i]) || remove[i] == '_'))
			return (1);
	}
	return (0);
}

void	b_unset(t_var *var, char **cmd)
{
	size_t	i;
	char	***env;

	if (!var->our_env || !cmd)
		return ;
	env = &var->our_env;
	i = 1;
	while (i < ft_sstrlen(cmd))
	{
		if (check_alnum_remove(cmd[i]) == 1)
		{
			printf_err("minishell: unset: \'");
			printf_err(cmd[i]);
			printf_err("\': not a valid identifier\n");
			g_exitcode = 1;
		}
		else
			*env = ft_removeonestring(*env, cmd[i], ft_sstrlen(*env));
		i++;
	}
}
