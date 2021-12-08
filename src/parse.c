#include "../header/minishell.h"
#include <string.h>

t_list *parse_line(char *line) {
	int		i;
	char	**comm_set;
	t_list	*result;
	// 일단 ;별로 나누어서 char**를 만들고, 
	comm_set = ft_split(line, ';');
	i = 0;
	result = ft_lstnew(comm_set[i++]);
	while (comm_set[i] != NULL) {
		ft_lstadd_back(&result, ft_lstnew(comm_set[i]));
	}
}