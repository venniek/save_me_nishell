#include "../header/minishell.h"

void	b_pwd(void)
{
	char	*buf;

	buf = getcwd(0, 100);
	printf("%s\n", buf);
	free(buf);
}
