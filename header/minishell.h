#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include "../libft/libft.h"

typedef struct s_ast {
    char            type;
    // exec에 들어갈 프로그램 + 옵션 입력 char**
    // -> exec함수에 바로 입력 가능한 형태로.
    char            **text;
    struct s_ast    *next;
} t_ast;

typedef struct s_var {
	char	*pwd_now;
	t_ast	*ast;
	char	**our_env;
} t_var;

void	*excep_malloc(int leng);
size_t	ft_sstrlen(char **strstr);
void	err_malloc();
t_ast	*parser(char *line, char **env);
char	**ft_addonestring(char **origin, char *newline);
char	**sstrncat(char **origin, char *newline, int n);


//=========naykim=========//
void	b_env(char **our_env);
void	b_cd(t_var *var, char **cmd);
void	b_pwd(void);
void	b_export(t_var *var, char **cmd);
void	b_unset(t_var *var, char **cmd);
void	b_echo(char **cmd);
int		b_exit(t_var *var);

void call_pwd(t_var *var);
char	**ft_sstrdup(char **origin);

#endif