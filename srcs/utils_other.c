/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naykim <naykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:48:52 by naykim            #+#    #+#             */
/*   Updated: 2022/01/22 16:07:26 by naykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

extern int	g_exitcode;

void	*excep_malloc(int leng)
{
	void	*result;

	result = malloc(leng);
	if (result == NULL)
		err_malloc();
	return (result);
}

void	*excep_calloc(size_t count, size_t size)
{
	void	*result;

	result = ft_calloc(count, size);
	if (result == NULL)
		err_malloc();
	return (result);
}

void	call_pwd(t_var *var)
{
	char	*str;
	char	*tmp_str;

	if (var->pwd_now)
		free(var->pwd_now);
	str = getcwd(0, 100);
	tmp_str = ft_strdup(ft_strrchr(str, '/'));
	free(str);
	str = ft_substr(tmp_str, 1, ft_strlen(tmp_str) - 1);
	free(tmp_str);
	tmp_str = ft_strjoin(str, "$ ");
	var->pwd_now = ft_strjoin("minishell-", tmp_str);
	free(str);
	str = 0;
	free(tmp_str);
	tmp_str = 0;
}
