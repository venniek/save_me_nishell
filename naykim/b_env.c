/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayeon <nayeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:09:07 by naykim            #+#    #+#             */
/*   Updated: 2022/01/11 17:13:47 by nayeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	b_env(char **our_env)
{
	int	i;

	if (!our_env)
		return ;
	i = -1;
	while (++i < ft_sstrlen(our_env))
		printf("%s\n", our_env[i]);
}
