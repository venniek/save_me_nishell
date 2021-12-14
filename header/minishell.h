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
# include "../libft/libft.h"

typedef struct s_env {
	char *key;
	char *value;
} t_env;

void	*excep_malloc(int leng);
size_t	ft_sstrlen(char **strstr);
void	err_malloc();


void b_cd(char *path);
void b_pwd();


#endif