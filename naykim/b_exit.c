#include "../header/minishell.h"

int b_exit()
{
	//free_all 같은 함수?
	printf("=== terminate our minishell ===\n");
	system("leaks minishell");
	exit(0);
}