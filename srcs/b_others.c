/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_others.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 16:34:28 by naykim            #+#    #+#             */
/*   Updated: 2022/01/25 13:42:43 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

extern int	g_exitcode;

void	b_cd(t_var *var, t_ast *ptr)
{
	if (!ptr->text)
		return ;
	if (!ptr->text[1])
	{
		if (input_home_in_cd(var, ptr) == 1)
			return ;
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

void	b_echo(char **cmd)
{
	int		n_option;
	size_t	idx;

	n_option = 0;
	if (!cmd)
		return ;
	idx = 1;
	echo_n_flag(cmd, &idx, &n_option);
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
	while (++i < (int)ft_sstrlen(var->our_env))
		if (ft_strchr(var->our_env[i], '=') != NULL)
			printf("%s\n", var->our_env[i]);
	g_exitcode = 0;
}

void	b_pwd(void)
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
	exit(i);
}
