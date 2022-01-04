#include "../header/minishell.h"

void b_export(char **env, char *new)
{
	if (!env || !new)
		return ;
	// "key=value" 형식인지 확인
	env = ft_addonestring(env, new);
}
