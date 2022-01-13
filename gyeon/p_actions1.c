//
// Created by 연규준 on 2022/01/13.
//

#include "../header/minishell.h"

void	action_idx(char **line, size_t *slide)
{
	*line += *slide;
	*slide = 0;
}

char	*action_cat(char *dst, char *src, size_t slide)
{
	char	*result;

	if (dst == NULL)
		result = ft_strndup(src, slide);
	else
	{
		result = malloc_n_lcat(dst, src, slide + ft_strlen(dst) + 1);
		free(dst);
	}
	return (result);
}

char	*action_env(char *dst, char *src, char **env, size_t slide)
{
	char	*result;
	char	*env_value;

	env_value = lookup_value(src, slide, env);
	if (env_value != NULL)
	{
		result = action_cat(dst, env_value, ft_strlen(env_value));
		free(env_value);
	}
	else
		return (NULL);
	return (result);
}