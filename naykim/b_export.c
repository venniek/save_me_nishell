#include "../header/minishell.h"

void b_export(char **env, char *new)
{
	if (!env || !new)
		return ;
	env = ft_addonestring(env, new);
}
