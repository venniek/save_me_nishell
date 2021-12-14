#include "../header/minishell.h"

void *excep_malloc(int leng) {
	void	*result;

	result = malloc(leng);
	if (result == NULL) 
		err_malloc();
	return (result);
}

size_t ft_sstrlen(char **strstr) {
	size_t leng;

	leng = 0;
	while (strstr[leng] != NULL)
		++leng;
	return (leng);
}

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