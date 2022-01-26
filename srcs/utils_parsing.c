/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:48:59 by naykim            #+#    #+#             */
/*   Updated: 2022/01/26 12:17:45 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

extern int	g_exitcode;

char	*lookup_value(char *start, size_t leng, char **env)
{
	size_t	idx;
	char	*temp;
	char	*result;

	idx = 0;
	result = NULL;
	if (leng == 0)
		return (ft_strdup("$"));
	else if (leng == 1 && ft_strncmp(start, "?", leng) == 0)
		return (ft_itoa(g_exitcode));
	temp = ft_strndup(start, leng);
	while (env[idx] != NULL)
	{
		if (ft_strncmp(env[idx], temp, ft_strlen(temp)) == 0)
		{
			if (env[idx][ft_strlen(temp)] == '=')
			{
				result = ft_strdup(&env[idx][ft_strlen(temp) + 1]);
				break ;
			}
		}
		++idx;
	}
	free(temp);
	return (result);
}

int	ft_isWhite(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
