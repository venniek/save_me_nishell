#include "minishell.h"

void	free_ast_in_var(t_var *var)
{
	if (!var)
		return ;
	free_ast(var->ast);
	var->ast = 0;
}

void	free_ast(t_ast *ast)
{
	t_ast	*next_node;

	while (ast)
	{
		next_node = ast->next;
		if (ast->text)
			free_sstr(ast->text);
		if (ast->rd_owrite)
			free_sstr(ast->rd_owrite);
		if (ast->rd_append)
			free_sstr(ast->rd_append);
		if (ast->rd_input)
			free_sstr(ast->rd_input);
		if (ast->heredoc)
			free_sstr(ast->heredoc);
		free(ast);
		ast = next_node;
	}
}

void	free_sstr(char **sstr)
{
	int	i;
	int	sstr_len;

	i = 0;
	if (!sstr)
		return ;
	while (sstr[i])
	{
		free(sstr[i]);
		sstr[i] = 0;
		i++;
	}
	if (sstr)
		free(sstr);
	sstr = 0;
}

void	free_pinfo(t_var *var)
{
	int	i;

	if (!var->pinfo)
		return ;
	i = -1;
	while (++i < var->pinfo->num_fds)
	{
		if (var->pinfo->fds[i])
		{
			free(var->pinfo->fds[i]);
			var->pinfo->fds[i] = 0;
		}
	}
	if (var->pinfo->fds)
	{
		free(var->pinfo->fds);
		var->pinfo->fds = 0;
	}
	if (var->pinfo)
	{
		free(var->pinfo);
		var->pinfo = 0;
	}
}
