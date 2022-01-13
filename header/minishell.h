#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include "defines.h"
# include "../libft/libft.h"

typedef struct s_ast {
    char            type;
    // exec에 들어갈 프로그램 + 옵션 입력 char**
    // -> exec함수에 바로 입력 가능한 형태로.
    char            **text;
    struct s_ast    *next;
} t_ast;

typedef struct s_parsing {
	t_ast 	*result;
	char 	*act;
	char	*cursor;
	char 	state;
	size_t 	slide;
} t_parsing;

void	*excep_malloc(int leng);
void	*excep_calloc(size_t count, size_t size);
size_t	ft_sstrlen(char **strstr);
void	err_malloc();

char	**ft_addonestring(char **origin, char *newline);
char	**sstrncat(char **origin, char *newline, int n);

#endif