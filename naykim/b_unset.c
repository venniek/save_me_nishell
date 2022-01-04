#include "../header/minishell.h"

int find_remove_str(char **origin, char *remove, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (ft_strncmp(origin[i], remove, ft_strlen(remove)))
			return (i);
		i++;
	}
	return (-1);
}

char **b_unset(char **origin, char *remove)
{
	char	**new;
	int		idxlen;
	int		i;
	int		newi;
	int		flag;

	if (!origin || !remove)
		return (NULL);
	idxlen = ft_sstrlen(origin);
	flag = find_remove_str(origin, remove, idxlen);
	if (flag != -1)
		new = (char **)malloc(sizeof(char *) * idxlen);
	else
		return (origin);
	i = -1;
	newi = 0;
	while (++i < idxlen)
	{
		if (i != flag)
			new[newi++] = ft_strdup(origin[i]);
	}
	new[idxlen] = 0;
	free(origin);
	origin = 0;
	return (new);
}


// int main(int ac, char **av, char **env)
// {
// 	char **new = b_unset(env, "PATH");
// 	for (int i = 0; i < ft_sstrlen(new); i++)
// 		printf("%s\n", new[i]);
// 	return 0;
// }