/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_others.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayeon <nayeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:34:28 by naykim            #+#    #+#             */
/*   Updated: 2022/01/23 17:59:34 by nayeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

extern int	g_exitcode;

void	b_cd(t_var *var, t_ast *ptr)
{
	char	*tmp;

	if (!ptr->text)
		return ;
	if (!ptr->text[1])
	{
		tmp = lookup_value("HOME", 4, var->our_env);
		if (!tmp)
		{
			printf_err("minishell: cd: HOME not set\n");
			free(tmp);
			g_exitcode = 1;
			return ;
		}
		ptr->text = ft_addonestring(ptr->text, tmp);
		ptr->text = ptr->text;
		free(tmp);
	}
	if (chdir(ptr->text[1]))
	{
		printf_err("minishell: cd: ");
		printf_err(ptr->text[1]);
		printf_err(": ");
		printf_err(strerror(errno));
		printf_err("\n");
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
