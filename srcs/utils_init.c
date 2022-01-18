#include "../header/minishell.h"

void init_var(t_var *var, char **env)
{
	var->ast = 0;
	var->ast_len = 0;
	var->our_env = ft_sstrdup(env);
	var->pwd_now = 0;
	var->pinfo = 0;
}

void init_pinfo(t_var *var)
{
	int	i;

	var->pinfo = (t_pipeinfo *)malloc(sizeof(t_pipeinfo) * 1);
	var->pinfo->cnt = 0;
	var->pinfo->child_pid = 0;
	var->pinfo->num_fds = var->ast_len;
	var->pinfo->fds = (int **)malloc(var->ast_len * sizeof(int *));
	if (var->pinfo->fds == NULL)
		exit(1);
	i = 0;
	while (i < var->ast_len)
	{
		var->pinfo->fds[i] = (int *)malloc(2 * sizeof(int));
		if (var->pinfo->fds[i++] == NULL)
			exit(1);
	}
}