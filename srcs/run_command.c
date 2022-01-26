/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:59:37 by gyeon             #+#    #+#             */
/*   Updated: 2022/01/26 15:00:37 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

extern int	g_exitcode;

void	only_one_command(t_var *var)
{
	run_func(var, var->ast, 1);
	free_ast_in_var(var);
}

void	run_func(t_var *var, t_ast *ptr, int flag)
{
	char	**cmds;

	if (!ptr->text || !ptr->text[0])
		return ;
	cmds = ptr->text;
	if (redirections(ptr) == 1)
		return ;
	if (!ft_strncmp(cmds[0], "cd", 2) && ft_strlen(cmds[0]) == 2)
		b_cd(var, ptr);
	else if (!ft_strncmp(cmds[0], "pwd", 3) && ft_strlen(cmds[0]) == 3)
		b_pwd();
	else if (!ft_strncmp(cmds[0], "env", 3) && ft_strlen(cmds[0]) == 3)
		b_env(var);
	else if (!ft_strncmp(cmds[0], "echo", 4) && ft_strlen(cmds[0]) == 4)
		b_echo(cmds);
	else if (!ft_strncmp(cmds[0], "export", 6) && ft_strlen(cmds[0]) == 6)
		b_export(var, cmds);
	else if (!ft_strncmp(cmds[0], "unset", 5) && ft_strlen(cmds[0]) == 5)
		b_unset(var, cmds);
	else if (!ft_strncmp(cmds[0], "exit", 4) && ft_strlen(cmds[0]) == 4)
		b_exit(var, have_argument(var, cmds));
	else if (flag == 1)
		b_exec_with_fork(var, cmds);
	else
		b_exec(var, cmds);
}

int	have_argument(t_var *var, char **cmds)
{
	unsigned char	ret;

	if (cmds[1])
	{
		if (ft_isdigit(cmds[1][0]) != 1)
		{
			printf_err("minishell: exit: ");
			printf_err(cmds[1]);
			printf_err(": numeric argument required\n");
			b_exit(var, 255);
		}
		if (ft_sstrlen(cmds) > 2)
		{
			g_exitcode = 1;
			return (printf_err("minishell: exit: too many arguments\n"));
		}
		ret = ft_atoi(cmds[1]);
	}
	else
		ret = 0;
	return (ret);
}
