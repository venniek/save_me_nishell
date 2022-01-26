/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:48:52 by naykim            #+#    #+#             */
/*   Updated: 2022/01/26 14:00:35 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

extern int	g_exitcode;

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

int	printf_err(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

int	input_home_in_cd(t_var *var, t_ast *ptr)
{
	char	*tmp;

	tmp = lookup_value("HOME", 4, var->our_env);
	if (!tmp)
	{
		free(tmp);
		g_exitcode = 1;
		return (printf_err("minishell: cd: HOME not set\n"));
	}
	ptr->text = ft_addonestring(ptr->text, tmp);
	free(tmp);
	return (0);
}
