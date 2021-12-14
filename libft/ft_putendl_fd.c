/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 12:39:10 by gyeon             #+#    #+#             */
/*   Updated: 2021/06/01 14:14:57 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	if (s == NULL || fd < 0)
		;
	else
	{
		while (*s)
			write(fd, s++, sizeof(char));
		write(fd, "\n", sizeof(char));
	}
}
