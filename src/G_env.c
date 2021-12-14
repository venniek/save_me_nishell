#include "../header/minishell.h"

char **make_envarr(char **env) {
	char **result;
	int		i;
	size_t	len_sstr;

	i = 0;
	len_sstr = ft_sstrlen(env);
	result = (char **)excep_malloc(sizeof(char *) * len_sstr);
	while(i < len_sstr) {
		result[i] = ft_strdup(env[i]);
		if (result[i] == NULL)
			err_malloc();
		++i;
	}
	result[i] = NULL;
	return result;
}

// char **add_envarr(char **env, ) {

// }