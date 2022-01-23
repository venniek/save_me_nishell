/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naykim <naykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:48:56 by naykim            #+#    #+#             */
/*   Updated: 2022/01/22 19:39:27 by naykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	**ft_sstrncat(char **origin, char *newline, int n)
{
	int		idx;
	int		idx_newline;
	int		len_str;
	char	*temp;
	char	*ptr_str;

	if (n < 0)
		return (ft_addonestring(origin, newline));
	if (ft_sstrlen(origin) == 0)
		origin = ft_addonestring(origin, "");
	ptr_str = origin[ft_sstrlen(origin) - 1];
	if (n > ft_strlen(newline))
		n = ft_strlen(newline);
	len_str = ft_strlen(ptr_str);
	temp = excep_malloc(len_str + n + 1);
	idx = -1;
	while (++idx < len_str)
		temp[idx] = ptr_str[idx];
	idx_newline = 0;
	while (idx < len_str + n)
		temp[idx++] = newline[idx_newline++];
	temp[len_str + n] = '\0';
	origin[ft_sstrlen(origin) - 1] = temp;
	free(ptr_str);
	return (origin);
}

size_t	ft_sstrlen(char **strstr)
{
	size_t	leng;

	leng = 0;
	if (!strstr)
		return (0);
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
	new = (char **)malloc(sizeof(char *) * (idxlen + 2));
	i = -1;
	while (++i < idxlen)
		new[i] = ft_strdup(origin[i]);
	new[idxlen] = ft_strdup(newline);
	new[idxlen + 1] = NULL;
	idxlen = 0;
	free_sstr(origin);
	origin = 0;
	return (new);
}

char	**ft_sstrdup(char **origin)
{
	int		i;
	int		env_len;
	char	**new_env;

	if (!origin)
		return (NULL);
	env_len = ft_sstrlen(origin);
	new_env = (char **)malloc(sizeof(char *) * (env_len + 1));
	i = -1;
	while (++i < env_len)
		new_env[i] = ft_strdup(origin[i]);
	new_env[i] = NULL;
	return (new_env);
}
