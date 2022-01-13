/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naykim <naykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:34:22 by naykim            #+#    #+#             */
/*   Updated: 2022/01/13 16:34:25 by naykim           ###   ########.fr       */
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

static char	**ft_removeonestring(char **origin, char *remove, int origin_len)
{
	char	**new;
	int		i;
	int		newi;
	int		flag;

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
	free_sstr(origin);
	return (new);
}

void	b_unset(t_var *var, char **cmd)
{
	int		i;
	char	***env;

	if (!var->our_env || !cmd)
		return ;
	env = &var->our_env;
	i = 1;
	while (i < ft_sstrlen(cmd))
	{
		if (ft_strrchr(cmd[i], '='))
			printf("unset: %s: invalid parameter name\n", cmd[i]);
		else
			*env = ft_removeonestring(*env, cmd[i], ft_sstrlen(*env));
		i++;
	}
}
