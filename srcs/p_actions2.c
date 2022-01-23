/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_actions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 21:24:19 by gyeon             #+#    #+#             */
/*   Updated: 2022/01/23 21:24:21 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	action_addonestring(t_parsing *ps)
{
	t_ast	*last;

	if (ps->buffer != NULL)
	{
		last = get_last(ps->result);
		if (ps->where == 'c' && (ps->buffer)[0] != '\0')
			last->text = ft_addonestring(last->text, ps->buffer);
		else if (ps->where == 'R')
			last->rd_owrite = ft_addonestring(last->rd_owrite, ps->buffer);
		else if (ps->where == 'r')
			last->rd_append = ft_addonestring(last->rd_append, ps->buffer);
		else if (ps->where == 'L')
			last->rd_input = ft_addonestring(last->rd_input, ps->buffer);
		else if (ps->where == 'l')
			last->heredoc = ft_addonestring(last->heredoc, ps->buffer);
		if (ps->where == 'R' || ps->where == 'r')
			last->last_out = ps->where;
		else if (ps->where == 'L' || ps->where == 'l')
			last->last_in = ps->where;
		free(ps->buffer);
		ps->buffer = NULL;
	}
	return ('s');
}

void	action_white(char **line, t_parsing *ps)
{
	*line += ps->slide;
	while (1)
	{
		if (**line == '\0' || !ft_isWhite(**line))
			break ;
		++(*line);
	}
	ps->where = 'c';
}

char	action_appendlist(t_parsing *ps)
{
	free(ps->buffer);
	add_ast(ps->result);
	ps->buffer = NULL;
	ps->where = 'c';
	return ('s');
}

char	action_fin(char *buffer)
{
	free(buffer);
	return ('F');
}
