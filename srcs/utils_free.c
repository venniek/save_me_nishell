/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:18:39 by gyeon             #+#    #+#             */
/*   Updated: 2022/01/26 15:18:41 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	free_ast_in_var(t_var *var)
{
	if (!var)
		return ;
	free_ast(var->ast);
	var->ast = 0;
}

void	free_ast(t_ast *ast)
{
	t_ast	*next_node;
	size_t	idx;

	while (ast)
	{
		next_node = ast->next;
		if (ast->text)
			free_sstr(ast->text);
		if (ast->rd_owrite)
			free_sstr(ast->rd_owrite);
		if (ast->rd_append)
			free_sstr(ast->rd_append);
		if (ast->rd_input)
			free_sstr(ast->rd_input);
		if (ast->heredoc)
		{
			idx = 0;
			while (ast->heredoc[idx] != NULL)
				unlink(ast->heredoc[idx++]);
			free_sstr(ast->heredoc);
		}
		free(ast);
		ast = next_node;
	}
}

void	free_sstr(char **sstr)
{
	int	i;

	i = 0;
	if (!sstr)
		return ;
	while (sstr[i])
	{
		free(sstr[i]);
		sstr[i] = 0;
		i++;
	}
	if (sstr)
		free(sstr);
	sstr = 0;
}

void	free_pinfo(t_var *var)
{
	int	i;

	if (!var->pinfo)
		return ;
	if (var->pinfo->fds)
	{
		i = -1;
		while (++i < var->pinfo->num_fds)
		{
			if (var->pinfo->fds[i])
			{
				free(var->pinfo->fds[i]);
				var->pinfo->fds[i] = 0;
			}
		}
		free(var->pinfo->fds);
		var->pinfo->fds = 0;
	}
	if (var->pinfo)
	{
		free(var->pinfo);
		var->pinfo = 0;
	}
}
