/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naykim <naykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:09:00 by naykim            #+#    #+#             */
/*   Updated: 2022/01/06 17:00:06 by naykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

// void b_echo(char **str)
// {
// 	int n_option = 0;

// 	if (!str)
// 	{
// 		printf("error - \n");
// 		return ;
// 	}
// 	if (ft_strncmp(str[1], "-n", 2) == 0)
// 	{
// 		n_option = 1;
// 		printf("%s", str[2]);
// 	}	
// 	else
// 		printf("%s", str[1]);
// 	if (n_option == 0)
// 		printf("\n");
// }

void b_echo(char *str)
{
	int n_option = 0;

	if (!str)
	{
		printf("error - \n");
		return ;
	}
	if (ft_strncmp(str, "-n", 2) == 0)
	{
		n_option = 1;
		printf("%s", ft_substr(str, 3, ft_strlen(str) - 3));
	}	
	else
		printf("%s", str);
	if (n_option == 0)
		printf("\n");
}
