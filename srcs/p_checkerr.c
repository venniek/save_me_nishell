
#include "../header/minishell.h"

int		is_emptyast(t_ast *ast)
{
	return (ast->text[0] == NULL && ast->rd_append[0] == NULL
		&& ast->rd_owrite[0] == NULL && ast->rd_input[0] == NULL
		&& ast->heredoc[0] == NULL);
}

t_ast	*check_result(t_ast *result)
{
	t_ast	*pre;
	t_ast	*ptr;

	if (result == NULL)
		return (NULL);
	pre = result;
	ptr = result->next;
	while (ptr != NULL)
	{
		if (is_emptyast(ptr))
		{
			free_ast(result);
			return (NULL);
		}
		pre = ptr;
		ptr = ptr->next;
	}
	return (result);
}