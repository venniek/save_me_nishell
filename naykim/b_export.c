/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naykim <naykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:09:13 by naykim            #+#    #+#             */
/*   Updated: 2022/01/06 18:25:39 by naykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void b_export(char ***env, char *new)
{
	int i;
	char **split_new;
	char **tmp_env = *env;

	if (!tmp_env || !new)
		return ;
	if (!ft_strrchr(new, '='))
		return ;
	split_new = ft_split(new, '=');
	printf("split_new: \n");
	for (int j = 0; j < ft_sstrlen(split_new); j++)
		printf("%s\n", split_new[j]);
	i = -1;
	while (++i < ft_sstrlen(tmp_env))
	{
		if (!ft_strncmp(tmp_env[i], split_new[0], ft_strlen(split_new[0])))
		{
			free(tmp_env[i]);
			tmp_env[i] = ft_strdup(new);
			return ;
		}
	}
	*env = ft_addonestring(tmp_env, new);
}
