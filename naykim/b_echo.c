/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayeon <nayeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:09:00 by naykim            #+#    #+#             */
/*   Updated: 2022/01/11 17:13:13 by nayeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	b_echo(char **cmd)
{
	int	n_option;
	int	idx;

	n_option = 0;
	idx = 1;
	if (!cmd)
	{
		printf("error - \n");
		return ;
	}
	if (ft_strncmp(cmd[idx], "-n", 2) == 0 && ft_strlen(cmd[idx]) == 2)
	{
		n_option = 1;
		idx++;
	}
	while (idx < ft_sstrlen(cmd))
	{
		printf("%s", cmd[idx]);
		idx++;
		if (idx != ft_sstrlen(cmd))
			printf(" ");
	}
	if (n_option == 0)
		printf("\n");
}
