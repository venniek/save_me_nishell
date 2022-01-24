/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naykim <naykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:34:22 by naykim            #+#    #+#             */
/*   Updated: 2022/01/24 16:06:56 by naykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

extern int	g_exitcode;

int	find_remove_str(char **origin, char *remove, int len)
{
	int		i;
	char	*add_equal;

	add_equal = ft_strjoin(remove, "=");
	i = 0;
	while (i < len)
	{
		if (!ft_strncmp(origin[i], remove, ft_strlen(remove)))
		{
			free(add_equal);
			return (i);
		}
		i++;
	}
	free(add_equal);
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
	size_t	i;
	char	***env;

	if (!var->our_env || !cmd)
		return ;
	env = &var->our_env;
	i = 1;
	while (i < ft_sstrlen(cmd))
	{
		if (ft_strrchr(cmd[i], '='))
		{
			printf_err("unset: ");
			printf_err(cmd[1]);
			printf_err(": invalid parameter name\n");
			g_exitcode = 1;
		}
		else
			*env = ft_removeonestring(*env, cmd[i], ft_sstrlen(*env));
		i++;
	}
}
