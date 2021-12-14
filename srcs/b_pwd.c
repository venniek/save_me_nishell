#include "../header/minishell.h"

void b_pwd()
{
	char *buf;

	buf = getcwd(0, 100);
	printf("%s\n", buf);
	free(buf);
}
