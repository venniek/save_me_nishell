#include "../header/minishell.h"

static int	find_remove_str(char **origin, char *remove, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (!ft_strncmp(origin[i], remove, ft_strlen(remove)))
			return (i);
		i++;
	}
	return (-1);
}

static char	**ft_removeonestring(char **origin, char *remove, int origin_len)
{
	char	**new;
	int		i;
	int		newi;
	int		flag;

	flag = find_remove_str(origin, remove, origin_len);
	if (flag != -1)
		new = (char **)malloc(sizeof(char *) * (origin_len));
	else
		return (origin);
	i = -1;
	newi = 0;
	while (++i < origin_len)
	{
		if (i != flag)
			new[newi++] = ft_strdup(origin[i]);
	}
	new[newi] = 0;
	i = -1;
	while (++i < origin_len)
		free(origin[i]);
	free(origin);
	return (new);
}

char	**b_unset(char **our_env, char **cmd)
{
	int		i;
	int		env_len;
	char	**new_env;

	if (!our_env || !cmd)
		return (NULL);
	env_len = ft_sstrlen(our_env);
	new_env = (char **)malloc(sizeof(char *) * (env_len + 1));
	i = -1;
	while (++i < env_len)
		new_env[i] = ft_strdup(our_env[i]);
	new_env[i] = NULL;
	i = 1;
	while (i < ft_sstrlen(cmd))
	{
		new_env = ft_removeonestring(new_env, cmd[i], ft_sstrlen(new_env));
		i++;
	}
	return (new_env);
}
