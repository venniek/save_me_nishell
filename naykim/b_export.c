#include "../header/minishell.h"

char	**ft_addonestring(char **origin, char *newline)
{
	char	**new;
	int		idxlen;
	int		i;

	idxlen = 0;
	while (origin[idxlen])
		idxlen++;
	new = (char **)malloc(sizeof(char *) * (idxlen + 1));
	i = -1;
	while (++i <= idxlen)
		new[i] = origin[i];
	new[idxlen + 1] = ft_strdup(newline);
	i = -1;
	free(origin);
	origin = 0;
	return (new);
}

void b_export(char **env, char *new)
{
	//error handle

	env = ft_addonestring(env, new);
}
