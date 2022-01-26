/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_syscalls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:58:08 by gyeon             #+#    #+#             */
/*   Updated: 2022/01/26 11:51:30 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	*excep_malloc(int leng)
{
	void	*result;

	result = malloc(leng);
	if (result == NULL)
	{
		write(2, "fatal : malloc false.\n", 22);
		exit(1);
	}
	return (result);
}

void	*excep_calloc(size_t count, size_t size)
{
	void	*result;

	result = ft_calloc(count, size);
	if (result == NULL)
	{
		write(2, "fatal : calloc false.\n", 22);
		exit(1);
	}
	return (result);
}

int	open_dup2_close(char *file, int options, int stream)
{
	int	fd;

	fd = open(file, options, 0666);
	if (fd < -1)
		return (0);
	dup2(fd, stream);
	close(fd);
	return (1);
}
