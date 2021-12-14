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

//
char	**sstrncat(char **origin, char *newline, int n)
{
	int		idx;
	int		idx_newline;
	int		len_str;
	char	*temp;
	char	*ptr_str;

	if (n < 0)
		return ft_addonestring(origin, newline);
	if (ft_sstrlen(origin) == 0)
		ft_addonestring(origin, "");
	ptr_str = origin[ft_sstrlen(origin) - 1];
	if (n > ft_strlen(newline))
		n = ft_strlen(newline);
	len_str = ft_strlen(ptr_str);
	temp = excep_malloc(len_str + n + 1);
	idx = 0;
	while (idx < len_str) {
		temp[idx] = ptr_str[idx];
		++idx;
	}
	idx_newline = 0;
	while (idx < len_str + n)
		temp[idx++] = newline[idx_newline++];
	return origin;
}