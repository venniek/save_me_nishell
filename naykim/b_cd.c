#include "../header/minishell.h"

void	b_cd(t_var *var, char **cmd)
{
	if (!cmd)
		return ;
	// if (!cmd[1])
	// 	env에서 $HOME 찾아서 cmd 바꾸기
	if (chdir(cmd[1]))
		printf("minishell: cd: %s: %s\n", cmd[1], strerror(errno));
}
