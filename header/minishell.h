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
# include "defines.h"
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

typedef struct s_parsing {
	t_ast 	*result;
	char 	*act;
	char	*cursor;
	char 	state;
	size_t 	slide;
} t_parsing;

//=========gyeon=========//
t_ast	*get_last(t_ast	*start);
char	*malloc_n_lcat(char *dst, char *src, size_t leng);
void	action_idx(char **line, size_t *slide);
char	*action_cat(char *dst, char *src, size_t slide);
char	*action_env(char *dst, char *src, char **env, size_t slide);
char	action_addonestring(t_ast *lst, char **cursor);
void	action_white(char **line, const size_t *slide);
char	action_appendlist(t_ast *result, char **cursor, const char *act);
char	action_fin(char *cursor);
t_ast	*init_ast();
void	add_ast(t_ast *front, char type);
size_t	actset_fin(char *flgs);
size_t	actset_siglequotes(char *flgs);
size_t	actset_dollar(char *flgs, char flg);
size_t	actset_noflgs(char *flgs, char flg);
size_t	decide_actset(char flg);
int		rev_flg(char *flgs, char flg);

//=========naykim=========//
void	b_env(char **our_env);
void	b_cd(t_var *var, char **cmd);
void	b_pwd(void);
void	b_export(t_var *var, char **cmd);
void	b_unset(t_var *var, char **cmd);
void	b_echo(char **cmd);
int		b_exit(t_var *var);

void 	call_pwd(t_var *var);
char	**ft_sstrdup(char **origin);

//=========srcs=========//
void	free_sstr(char **sstr);
void	free_ast(t_ast *ast);
void	*excep_malloc(int leng);
void	*excep_calloc(size_t count, size_t size);
size_t	ft_sstrlen(char **strstr);
void	err_malloc();
char	**ft_addonestring(char **origin, char *newline);
char	**sstrncat(char **origin, char *newline, int n);
char	*lookup_value(char *start, size_t leng, char **env);
int		ft_isWhite(char c);


#endif