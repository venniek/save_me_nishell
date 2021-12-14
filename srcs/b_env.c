#include "../header/minishell.h"

void b_env(char **our_env)
{
	int i;

	if (!our_env)
		return ;
	i = -1;
	while (our_env[++i])   //몇줄인지 세는 걸 이런 식으로 해도 될까요?
	{
		printf("%s\n", our_env[i]);
	}
}

int main(int ac, char **av, char **env)
{
	b_env(env);
	return 0;
}