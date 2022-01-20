/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_others.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naykim <naykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:34:28 by naykim            #+#    #+#             */
/*   Updated: 2022/01/20 15:21:48 by naykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	b_cd(t_var *var, char **cmd)
{
	if (!cmd)
		return ;
	if (!cmd[1])
	{
		cmd[1] = lookup_value("HOME", 4, var->our_env);
		cmd[2] = 0;
	}
	if (chdir(cmd[1]))
		printf("minishell: cd: %s: %s\n", cmd[1], strerror(errno));
}

void	b_echo(char **cmd)
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
}

void	b_env(char **our_env)
{
	int	i;

	if (!our_env)
		return ;
	i = -1;
	while (++i < ft_sstrlen(our_env))
		printf("%s\n", our_env[i]);
}

void	b_pwd(void)
{
	char	*buf;

	buf = getcwd(0, 100);
	printf("%s\n", buf);
	free(buf);
}

int	b_exit(t_var *var, int i)
{
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
	printf("✅✅✅✅\nterminate our minishell ===\n✅✅✅✅ leak check\n");
	system("leaks minishell");
	exit(i);
}
