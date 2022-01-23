/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:51:24 by naykim            #+#    #+#             */
/*   Updated: 2022/01/23 21:30:06 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

extern int	g_exitcode;

char	**init_sstr(void)
{
	char	**result;

	result = (char **)excep_malloc(sizeof(char *) * 1);
	result[0] = NULL;
	return (result);
}

void	init_var(t_var *var, char **env)
{
	var->ast = 0;
	var->ast_len = 0;
	g_exitcode = 0;
	var->our_env = ft_sstrdup(env);
	var->pwd_now = 0;
	var->pinfo = 0;
}

void	init_pinfo(t_var *var)
{
	int	i;

	var->pinfo = (t_pipeinfo *)malloc(sizeof(t_pipeinfo) * 1);
	var->pinfo->cnt = 0;
	var->pinfo->child_pid = 0;
	var->pinfo->num_fds = var->ast_len;
	var->pinfo->fds = (int **)malloc(var->ast_len * sizeof(int *));
	if (var->pinfo->fds == NULL)
		exit(1);
	i = 0;
	while (i < var->ast_len)
	{
		var->pinfo->fds[i] = (int *)malloc(2 * sizeof(int));
		if (var->pinfo->fds[i++] == NULL)
			exit(1);
	}
}
