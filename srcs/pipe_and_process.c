/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naykim <naykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:59:05 by naykim            #+#    #+#             */
/*   Updated: 2022/01/21 16:19:12 by naykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

extern int	g_exitcode;

void	child_process(t_var *var)
{
	int	now_cnt;

	if (var->pinfo->cnt != var->pinfo->num_fds)
	{
		close(var->pinfo->fds[var->pinfo->cnt][1]);
		dup2(var->pinfo->fds[var->pinfo->cnt][0], STDIN_FILENO);
	}
	if (var->pinfo->cnt >= 2)
		dup2(var->pinfo->fds[var->pinfo->cnt - 1][1], STDOUT_FILENO);
	now_cnt = var->pinfo->num_fds - var->pinfo->cnt;
	run_func(var, ft_astindex(var->ast, now_cnt), 0);
	close(var->pinfo->fds[var->pinfo->cnt - 1][0]);
	exit(g_exitcode);
}

int	parent_process(t_var *var)
{
	int	i;
	int	stat_loc;

	waitpid(var->pinfo->child_pid, &stat_loc, 0);
	g_exitcode = WEXITSTATUS(stat_loc);
	if (var->pinfo->cnt == 0)
	{
		close(var->pinfo->fds[0][0]);
		close(var->pinfo->fds[0][1]);
		free_ast_in_var(var);
		free_pinfo(var);
		return (1);
	}
	return (0);
}

void	make_pipe_and_child(t_var *var)
{
	while (var->pinfo->cnt < var->ast_len)
	{
		if (pipe(var->pinfo->fds[var->pinfo->cnt]) == -1)
			b_exit(var, 1);
		var->pinfo->child_pid = fork();
		if (var->pinfo->child_pid == -1)
			b_exit(var, 1);
		else if (var->pinfo->child_pid != 0)
			break ;
		++(var->pinfo->cnt);
	}
}
