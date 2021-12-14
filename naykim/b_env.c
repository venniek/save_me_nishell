#include "../header/minishell.h"

void b_env(char **our_env)
{
	int i;

	if (!our_env)
		return ;
	i = -1;
	while (our_env[++i])
	{
		printf("%s\n", our_env[i]);
	}
}

int main(int ac, char **av, char **env)
{
	b_env(env);
	return 0;
}