/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_syscalls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:58:08 by gyeon             #+#    #+#             */
/*   Updated: 2022/01/26 15:17:10 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	*excep_malloc(int leng)
{
	void	*result;

	result = malloc(leng);
	if (result == NULL)
		exit(printf_err("fatal : malloc false.\n"));
	return (result);
}

void	*excep_calloc(size_t count, size_t size)
{
	void	*result;

	result = ft_calloc(count, size);
	if (result == NULL)
		exit(printf_err("fatal : calloc false.\n"));
	return (result);
}

int	open_dup2_close(char *file, int options, int stream)
{
	int	fd;

	fd = open(file, options, 0666);
	if (fd < -1)
	{
		printf_err("minishell: ");
		printf_err(file);
		return (printf_err(": No such file or directory\n"));
	}
	dup2(fd, stream);
	close(fd);
	return (0);
}
