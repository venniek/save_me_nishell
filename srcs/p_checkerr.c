/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_checkerr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 21:24:27 by gyeon             #+#    #+#             */
/*   Updated: 2022/01/24 20:25:03 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

extern int	g_exitcode;

int	is_emptyast(t_ast *ast)
{
	t_ast	*next;

	if (ast->text[0] == NULL && ast->rd_append[0] == NULL
		&& ast->rd_owrite[0] == NULL && ast->rd_input[0] == NULL
		&& ast->heredoc[0] == NULL && ast->next != NULL)
		return (1);
	else
	{
		if (ast->next != NULL)
		{
			next = ast->next;
			if (next->text[0] == NULL && next->rd_append[0] == NULL
				&& next->rd_owrite[0] == NULL && next->rd_input[0] == NULL
				&& next->heredoc[0] == NULL)
				return (1);
		}
	}
	return (0);
}

int	there_is_empty_redirection(t_ast *ast)
{
	size_t	idx;
	t_ast	*ptr;

	ptr = ast;
	while (ptr != NULL)
	{
		idx = 0;
		while (ptr->heredoc[idx] != NULL)
			if (ft_strncmp(ptr->heredoc[idx++], "", 1) == 0)
				return (1);
		idx = 0;
		while (ptr->rd_append[idx] != NULL)
			if (ft_strncmp(ptr->rd_append[idx++], "", 1) == 0)
				return (1);
		idx = 0;
		while (ptr->rd_input[idx] != NULL)
			if (ft_strncmp(ptr->rd_input[idx++], "", 1) == 0)
				return (1);
		idx = 0;
		while (ptr->rd_owrite[idx] != NULL)
			if (ft_strncmp(ptr->rd_owrite[idx++], "", 1) == 0)
				return (1);
		ptr = ptr->next;
	}
	return (0);
}

t_ast	*check_result(t_ast *result)
{
	t_ast	*ptr;

	if (result == NULL)
		return (NULL);
	ptr = result;
	while (ptr != NULL)
	{
		if (is_emptyast(ptr) == 0
			&& there_is_empty_redirection(ptr) == 0);
		else
		{
			g_exitcode = 258;
			free_ast(result);
			return (NULL);
		}
		ptr = ptr->next;
	}
	return (result);
}
