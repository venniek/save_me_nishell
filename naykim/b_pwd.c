#include "../header/minishell.h"

void	b_pwd(void)
{
	char	*buf;

	buf = getcwd(0, 100);
	printf("%s\n", buf);
	free(buf);
}

void	call_pwd(t_var *var)
{
	if (var->pwd_now)
		free(var->pwd_now);
	var->pwd_now = getcwd(0, 100);
}
