/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_others.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naykim <naykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:34:28 by naykim            #+#    #+#             */
/*   Updated: 2022/01/22 19:50:18 by naykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

extern int	g_exitcode;

void	b_cd(t_var *var, char **cmd)
{
	char *tmp;

	if (!cmd)
		return ;
	if (!cmd[1])
	{
		// tmp = lookup_value("HOME", 4, var->our_env);
		// cmd = ft_addonestring(cmd, tmp);
		// free(tmp);
		// tmp = 0;
		cmd[1] = lookup_value("HOME", 4, var->our_env);
		cmd[2] = 0;
	}
	if (chdir(cmd[1]))
	{
		printf("minishell: cd: %s: %s\n", cmd[1], strerror(errno));
		g_exitcode = 1;
		return ;
	}
	g_exitcode = 0;
}

void	b_echo(t_var *var, char **cmd)
{
	int	n_option;
	int	idx;

	n_option = 0;
	if (!cmd)
		return ;
	if (cmd[1] && ft_strlen(cmd[1]) == 2 && ft_strncmp(cmd[1], "-n", 2) == 0)
	{
		n_option = 1;
		idx = 2;
	}
	else
		idx = 1;
	while (idx < ft_sstrlen(cmd))
	{
		printf("%s", cmd[idx]);
		idx++;
		if (idx != ft_sstrlen(cmd))
			printf(" ");
	}
	if (n_option == 0)
		printf("\n");
	g_exitcode = 0;
}

void	b_env(t_var *var)
{
	int	i;

	if (!var->our_env)
		return ;
	i = -1;
	while (++i < ft_sstrlen(var->our_env))
		printf("%s\n", var->our_env[i]);
	g_exitcode = 0;
}

void	b_pwd(t_var *var)
{
	char	*buf;

	buf = getcwd(0, 100);
	printf("%s\n", buf);
	free(buf);
	g_exitcode = 0;
}

int	b_exit(t_var *var, int i)
{
	// if (ft_sstrlen(cmd) > 2)
	// {
	// 	printf("minishell: exit: too many arguments\n");
	// 	g_exitcode = 1;
	// 	return (1);
	// }
	if (var->ast)
		free_ast_in_var(var);
	if (var->our_env)
	{
		free_sstr(var->our_env);
		var->our_env = 0;
	}
	if (var->pwd_now)
	{
		free(var->pwd_now);
		var->pwd_now = 0;
	}
	if (var->pinfo)
		free_pinfo(var);
	g_exitcode = i;
	printf("✅✅✅✅\nterminate our minishell ===\n✅✅✅✅ leak check\n");
	// system("leaks minishell");
	exit(i);
}
