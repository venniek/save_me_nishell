/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayeon <nayeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:09:21 by naykim            #+#    #+#             */
/*   Updated: 2022/01/11 17:12:12 by nayeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include <errno.h>

void	b_cd(char **cmd)
{
	if (!cmd)
		return ;
	if (chdir(cmd[1]))
		printf("minishell: cd: %s: %s\n", cmd[1], strerror(errno));
}
