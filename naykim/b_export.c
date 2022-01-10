#include "../header/minishell.h"

void b_export(char **env, char *new)
{
	if (!env || !new)
		return ;
	// "key=value" 형식인지 확인
	// 원래 있던 거면 변경, 없던 거면 추가
	/*
	for (int i = 0; env[i]; i++)
	{
		if (strcmp(env[i], new, strlen(new[[키값만 비교. = 나오기전까지]])) == 0)
		{
			env[i] = new
			return ;
		}
	}
	*/
	env = ft_addonestring(env, new);
}
