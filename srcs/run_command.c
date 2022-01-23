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
	if (redirections(ptr) == 0)
		return ;
	if (!ft_strncmp(cmds[0], "cd", 2) && ft_strlen(cmds[0]) == 2)
		return (b_cd(var, ptr));
	if (!ft_strncmp(cmds[0], "pwd", 3) && ft_strlen(cmds[0]) == 3)
		return (b_pwd(var));
	if (!ft_strncmp(cmds[0], "env", 3) && ft_strlen(cmds[0]) == 3)
		return (b_env(var));
	if (!ft_strncmp(cmds[0], "echo", 4) && ft_strlen(cmds[0]) == 4)
		return (b_echo(var, cmds));
	if (!ft_strncmp(cmds[0], "export", 6) && ft_strlen(cmds[0]) == 6)
		return (b_export(var, cmds));
	if (!ft_strncmp(cmds[0], "unset", 5) && ft_strlen(cmds[0]) == 5)
		return (b_unset(var, cmds));
	if (!ft_strncmp(cmds[0], "exit", 4) && ft_strlen(cmds[0]) == 4)
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
		printf_err("minishell: exit: too many arguments\n");
		g_exitcode = 1;
		return (1);
	}
		ret = ft_atoi(cmds[1]);
	}
	else
		ret = 0;
	return (ret);
}
