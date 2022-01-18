#include "../header/minishell.h"

void	prt_sstr(char **sstr)
{
	size_t	i = 0;
	if (sstr == NULL)
		return ;
	while (sstr[i] != NULL)
		printf("\t%s\n", sstr[i++]);
}

void	prt_allast(t_ast *ast)
{
	t_ast	*ptr;

	ptr = ast;
	while (ptr != NULL)
	{
		printf("[ast->text]---------\n");
		prt_sstr(ptr->text);
		printf("[ast->rd_owrite]----\n");
		prt_sstr(ptr->rd_owrite);
		printf("[ast->rd_append]----\n");
		prt_sstr(ptr->rd_append);
		printf("[ast->rd_input]-----\n");
		prt_sstr(ptr->rd_input);
		printf("[ast->heredoc]------\n");
		prt_sstr(ast->heredoc);
		ptr = ptr->next;
	}
	return ;
}

