#include "../header/minishell.h"

void free_ast(t_ast *ast)
{
	int i;

	while (ast)
	{
		i = -1;
		while (++i < ft_sstrlen(ast->text))
		{
			free(ast->text[i]);
			ast->text[i] = 0;
		}
		free(ast->text);
		ast = ast->next;
	}
}

void free_env(char **env)
{
	int i;
	int env_len;

	i = -1;
	env_len = ft_sstrlen(env);
	while (++i < env_len)
	{
		free(env[i]);
		env[i] = 0;
	}
	free(env);
}

int	b_exit(t_var *var)
{
	if (var->ast)
	{
		free_ast(var->ast);
		var->ast = 0;
	}
	printf("after free ast\n");
	if (var->our_env)
	{
		free_env(var->our_env);
		var->our_env = 0;
	}
	printf("after free our_env\n");
	if (var->pwd_now)
	{
		free(var->pwd_now);
		var->pwd_now = 0;
	}
	printf("after free pwd_now\n");
	printf("=== terminate our minishell ===\n");
	system("leaks minishell");
	exit(0);
}
