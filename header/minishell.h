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

typedef struct s_name {
    char    *text;
    char    *type;

} t_name;

/* type
 * 음수 : fork할 개수... -> 리다이렉션, 파이프 포함.
 * 0 : 그냥 명령어 ->
 * 1 : 리다이렉션 문자
 * 2 : file
*/

typedef struct s_file {
    int     fd;
    char    *name;
} t_file;

typedef struct s_ast {
    char            type;
    // 밑에, s_ast, text, file은 union으로 묶기.
    // pipe, redirection시 사용
    struct s_ast    *commands;
    // exec에 들어갈 프로그램 + 옵션 입력 char**
    // -> exec함수에 바로 입력 가능한 형태로.
    char            **text;
    struct s_file   *info_file;
    // ; 단위로 끊기
    struct s_ast    *next;
} t_ast;

void	*excep_malloc(int leng);
size_t	ft_sstrlen(char **strstr);
void	err_malloc();
t_ast	*paser(char *line);
char	**ft_addonestring(char **origin, char *newline);
char	**sstrncat(char **origin, char *newline, int n);

#endif