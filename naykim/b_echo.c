#include "../header/minishell.h"

void b_echo(char **str)
{
	int n_option = 0;

	if (!str)
	{
		printf("error - \n");
		return ;
	}
	if (ft_strncmp(str[1], "-n", 2) == 0)
	{
		n_option = 1;
		printf("%s", str[2]);
	}	
	else
		printf("%s", str[1]);
	if (n_option == 0)
		printf("\n");
}
