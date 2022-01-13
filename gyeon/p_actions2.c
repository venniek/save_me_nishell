//
// Created by 연규준 on 2022/01/13.
//

#include "../header/minishell.h"

char	action_addonestring(t_ast *lst, char **cursor)
{
	if ((*cursor)[0] != '\0')
	{
		lst = get_last(lst);
		lst->text = ft_addonestring(lst->text, *cursor);
		free(*cursor);
	}
	*cursor = NULL;
	return ('s');
}

void action_white(char **line, const size_t *slide)
{
	*line += *slide;
	while (1) {
		if (**line == '\0' || !ft_isWhite(**line))
			break;
		++(*line);
	}
}

char action_appendlist(t_ast *result, char **cursor, const char *act)
{
	free(*cursor);
	add_ast(result, *act);
	cursor = NULL;
	return 's';
}

char action_fin(char *cursor)
{
	free(cursor);
	return ('F');
}