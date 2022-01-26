/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_err_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:49:22 by naykim            #+#    #+#             */
/*   Updated: 2022/01/26 13:59:56 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

extern int	g_exitcode;

int	if_have_slash(char **cmd)
{
	DIR		*temp_dir;
	int		temp_fd;

	printf_err("minishell: ");
	printf_err(cmd[0]);
	temp_dir = opendir(cmd[0]);
	if (temp_dir == NULL)
	{
		temp_fd = open(cmd[0], O_RDONLY);
		if (temp_fd < 0)
		{
			g_exitcode = 127;
			return (printf_err(": No such file or directory\n"));
		}
		close(temp_fd);
		g_exitcode = 126;
		return (printf_err(": is not executable file\n"));
	}
	closedir(temp_dir);
	g_exitcode = 126;
	return (printf_err(": is a directory\n"));
}
