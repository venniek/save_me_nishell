#include "../header/minishell.h"

char	*lookup_value(char *start, size_t leng, char **env)
{
	size_t	idx;
	char	*temp;
	char	*result;

	idx = 0;
	result = NULL;
	temp = ft_strndup(start, leng);
	while (env[idx] != NULL)
	{
		if (ft_strncmp(env[idx], temp, ft_strlen(temp)) == 0)
		{
			if (env[idx][ft_strlen(temp)] == '=')
				result = ft_strdup(&env[idx][ft_strlen(temp) + 1]);
		}
		++idx;
	}
	free(temp);
	return (result);
}

void	b_cd(t_var *var, char **cmd)
{
	if (!cmd)
		return ;
	if (!cmd[1])
		cmd[1] = lookup_value("HOME", 4, var->our_env);
	if (chdir(cmd[1]))
		printf("minishell: cd: %s: %s\n", cmd[1], strerror(errno));
}
