#include "../header/minishell.h"

char **b_unset(char **origin, char *remove)
{
	char	**new;
	int		idxlen;
	int		i;
	int		newi;
	int		flag = 0;

	if (!origin)
		return (NULL);
	if (!remove)
		return (NULL);
	idxlen = 0;
	while (origin[idxlen])
		idxlen++;
	i = 0;
	while (i < idxlen)
	{
		if (ft_strncmp(origin[i], remove, ft_strlen(remove)))
			flag = 1;
		i++;
	}
	if (flag == 1)
		new = (char **)malloc(sizeof(char *) * idxlen);
	else
		return (origin);
	i = -1;
	newi = 0;
	while (++i < idxlen)
	{
		if (!ft_strncmp(origin[i], remove, ft_strlen(remove)))
			new[newi++] = origin[i];
		else
			free(origin[i]);
	}
	new[idxlen] = 0;
	free(origin);
	origin = 0;
	return (new);
}