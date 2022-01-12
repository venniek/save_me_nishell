#include "../header/minishell.h"

void	b_cd(char **cmd)
{
	if (!cmd)
		return ;
	if (chdir(cmd[1]))
		printf("minishell: cd: %s: %s\n", cmd[1], strerror(errno));
}
