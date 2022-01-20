/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:59:05 by naykim            #+#    #+#             */
/*   Updated: 2022/01/20 21:28:24 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
 * fds : 
*/
int	redirections(t_ast *ast)
{
	size_t	rd;
	size_t	idx;
	size_t	len_sstr;
	char	**ptr[4];
	int		*fds[4];

	rd = 0;
	ptr[0] = ast->heredoc;		// l
	ptr[1] = ast->rd_append;	// r
	ptr[2] = ast->rd_input;		// R
	ptr[3] = ast->rd_owrite;	// L
	while (rd < 4)
	{
		idx = 0;
		len_sstr = ft_sstrlen(ptr[rd]);
		fds[rd] = (int *)excep_malloc(sizeof(int) * len_sstr);
		while (idx < len_sstr)
		{
			printf("%zu : %s\n", rd, ptr[rd][idx]);
			if (rd == 0) //heredoc 임시파일 open,
				;	
			else if (rd == 1) // append
				fds[rd][idx] = open(ptr[rd][idx], O_WRONLY | O_CREAT, 0666);
			else if (rd == 2) // input
				fds[rd][idx] = open(ptr[rd][idx], O_RDONLY);
			else //rd == 3, owrite
				fds[rd][idx] = open(ptr[rd][idx], O_WRONLY | O_TRUNC | O_CREAT, 0666);
			if (fds[rd][idx] < 0)
			{
				printf("%s: No such file or directory\n", ptr[rd][idx]);
				return 0;
			}
			else
				printf("%s: %d\n", ptr[rd][idx], fds[rd][idx]);
			idx++;
		}
		rd++;
	}
	if (ast->last_in == 'l')
		; //dup2(fds[0][ft_sstrlen(ptr[0])], STDIN_FILENO);
	else if (ast->last_in == 'r')
		dup2(fds[1][ft_sstrlen(ptr[1])], STDOUT_FILENO);
	else if (ast->last_in == 'R')
		dup2(fds[2][ft_sstrlen(ptr[2])], STDOUT_FILENO);
	else // L
		dup2(fds[3][ft_sstrlen(ptr[3])], STDIN_FILENO);
	while (rd < 4)
		free(fds[rd++]);
	return 1;
}

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
	redirections(var->ast);
	now_cnt = var->pinfo->num_fds - var->pinfo->cnt;
	run_func(var, ft_astindex(var->ast, now_cnt), 0);
	close(var->pinfo->fds[var->pinfo->cnt - 1][0]);
	exit(0);
}

int	parent_process(t_var *var)
{
	int	i;
	int	stat_loc;

	waitpid(var->pinfo->child_pid, &stat_loc, 0);
	if (var->pinfo->cnt == 0)
	{
		close(var->pinfo->fds[0][0]);
		close(var->pinfo->fds[0][1]);
		free_ast_in_var(var);
	}
	if (WEXITSTATUS(stat_loc) != 0)
		exit(WEXITSTATUS(stat_loc));
	else if (var->pinfo->cnt == 0)
	{
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
