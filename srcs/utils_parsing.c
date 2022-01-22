/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naykim <naykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:48:59 by naykim            #+#    #+#             */
/*   Updated: 2022/01/20 20:11:22 by naykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
