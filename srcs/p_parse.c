#include "../header/minishell.h"

char	*get_actset(size_t idx)
{
	static char	*actset[22] =
			{"J", "CJI", "EJI", "EIJ", "CJIAP",
			 "CJIAR", "CJJIAr", "CJIAL", "CJJIAl", "EJIAP",
			 "EJIAR", "EJJIAr", "EJIAL", "EJJIAl", "CJIAW",
			 "EJIAW", "CAF", "EAF", "HJI", "e", "CJIEJI", "EJIEJI"};

	return (actset[idx]);
}

char	c_to_h(t_parsing *ps, char **env, char **line)
{
	char		state;

	state = 'm';
	if (*ps->act == 'C')
		ps->buffer = action_cat(ps->buffer, *line, ps->slide);
	else if (*ps->act == 'E')
		ps->buffer = action_env(ps->buffer, *line, env, ps->slide);
	else if (*ps->act == 'H')
		ps->buffer = action_env(ps->buffer, "HOME", env, 4);
	else if (*ps->act == 'F')
		state = action_fin(ps->buffer);
	return (state);
}

char	i_to_w(t_parsing *ps, char **line)
{
	char		state;

	state = 'm';
	if (*ps->act == 'J')
		++(ps->slide);
	else if (*ps->act == 'I')
		action_idx(line, &ps->slide);
	else if (*ps->act == 'W')
		action_white(line, ps);
	else if (*ps->act == 'P')
		state = action_appendlist(ps);
	else if (*ps->act == 'R' || *ps->act == 'r'
		|| *ps->act == 'L' || *ps->act == 'l')
	{
		action_white(line, ps);
		ps->where = *ps->act;
		state = 's';
	}
	return (state);
}

void	init_parsing(t_parsing *parsing)
{
	parsing->buffer = NULL;
	parsing->result = init_ast();
	parsing->slide = 0;
	parsing->state = 's';
	parsing->where = 'c';
}

t_ast	*parser(char *line, char **env)
{
	t_parsing	ps;

	init_parsing(&ps);
	while (ps.state != 'F')
	{
		ps.act = get_actset(get_actindex(&line[ps.slide], ps.state));
		ps.state = 'm';
		while (*ps.act != '\0')
		{
			if (*ps.act == 'A')
				ps.state = action_addonestring(&ps);
			else if (*ps.act == 'e')
				action_err(&ps);
			else if (*ps.act <= 'H')
				ps.state = c_to_h(&ps, env, &line);
			else
				i_to_w(&ps, &line);
			++ps.act;
		}
	}
	return (check_result(ps.result));
}
