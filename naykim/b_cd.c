#include "../header/minishell.h"

void b_cd(char *path)
{
	if (!path)
		return (NULL);
	if (!chdir(path))
		printf("error during cd\n");

}
