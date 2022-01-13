#include "../header/minishell.h"

void	free_ast(t_ast *ast)
{
	while (ast)
	{
		free_sstr(ast->text);
		ast->text = 0;
		ast = ast->next;
	}
}

void	free_sstr(char **sstr)
{
	int	i;
	int	sstr_len;

	i = -1;
	sstr_len = ft_sstrlen(sstr);
	while (++i < sstr_len)
	{
		free(sstr[i]);
		sstr[i] = 0;
	}
	free(sstr);
	sstr = 0;
}

int	b_exit(t_var *var)
{
	if (var->ast)
	{
		free_ast(var->ast);
		var->ast = 0;
	}
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
	printf("=== terminate our minishell ===\n");
	system("leaks minishell");
	exit(0);
}
