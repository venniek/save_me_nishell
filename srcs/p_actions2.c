//
// Created by 연규준 on 2022/01/13.
//

#include "../header/minishell.h"

//char	action_addonestring(t_ast *lst, char **buffer)
char	action_addonestring(t_parsing *ps)
{
	t_ast	*last;
	if (ps->buffer != NULL)
	{
		if ((ps->buffer)[0] != '\0')
		{
			last = get_last(ps->result);
			if (ps->where == 'c')
				last->text = ft_addonestring(last->text, ps->buffer);
			else if (ps->where == 'R')
				last->rd_owrite = ft_addonestring(last->rd_owrite, ps->buffer);
			else if (ps->where == 'r')
				last->rd_append = ft_addonestring(last->rd_append, ps->buffer);
			else if (ps->where == 'L')
				last->rd_input = ft_addonestring(last->rd_input, ps->buffer);
			else if (ps->where == 'l')
				last->heredoc = ft_addonestring(last->heredoc, ps->buffer);
			free(ps->buffer);
			ps->buffer = NULL;
		}
	}
	return ('s');
}

void action_white(char **line, t_parsing *ps)
{
	*line += ps->slide;
	while (1) {
		if (**line == '\0' || !ft_isWhite(**line))
			break;
		++(*line);
	}
	ps->where = 'c';
}

//char action_appendlist(t_ast *result, char **buffer, const char *act)
char action_appendlist(t_parsing *ps)
{
	// free(*buffer);
	// add_ast(result, *act);
	// buffer = NULL;
	// return 's';
	free(ps->buffer);
	add_ast(ps->result, 'c');
	ps->buffer = NULL;
	ps->where = 'c';
	return 's';
}

char action_fin(char *buffer)
{
	free(buffer);
	return ('F');
}