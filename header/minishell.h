/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayeon <nayeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:50:17 by naykim            #+#    #+#             */
/*   Updated: 2022/01/18 02:32:53 by nayeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_ast
{
    char            type;
    // exec에 들어갈 프로그램 + 옵션 입력 char**
    // -> exec함수에 바로 입력 가능한 형태로.
    char            **text;
    struct s_ast    *next;
} t_ast;

typedef struct s_pipeinfo
{
	int	cnt;
	int	child_pid;
	int	num_fds;
	int	**fds;
} t_pipeinfo;

typedef struct s_var
{
	char		*pwd_now;
	char		**our_env;
	int			ast_len;
	t_ast		*ast;
	t_pipeinfo	*pinfo;
} t_var;

typedef struct s_parsing
{
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
size_t	decide_actset(char flg);
int		rev_flg(char *flgs, char flg);
t_ast	*parser(char *line, char **env);
char	**ft_addonestring(char **origin, char *newline);
char	**sstrncat(char **origin, char *newline, int n);
char	*lookup_value(char *start, size_t leng, char **env);
size_t	get_actindex(const char *str, const char state);

//=========naykim=========//
void	b_env(char **our_env);
void	b_cd(t_var *var, char **cmd);
void	b_pwd(void);
void	b_export(t_var *var, char **cmd);
void	b_unset(t_var *var, char **cmd);
void	b_echo(char **cmd);
int		b_exit(t_var *var);
void	b_exec(t_var *var, char **cmds);
void	run_command(char **cmds, char **env);
void	find_cmd(char **path, int i, char **cmd, char **env);
char	**make_paths(char **env);

//=========srcs=========//
char	**ft_sstrdup(char **origin);
void 	call_pwd(t_var *var);
void	free_sstr(char **sstr);
void	free_ast(t_ast *ast);
void	init_var(t_var *var, char **env);
void	run_func(t_var *var, t_ast *ptr);
void	*excep_malloc(int leng);
void	*excep_calloc(size_t count, size_t size);
size_t	ft_sstrlen(char **strstr);
void	err_malloc();
char	**ft_addonestring(char **origin, char *newline);
char	**sstrncat(char **origin, char *newline, int n);
char	*lookup_value(char *start, size_t leng, char **env);
int		ft_isWhite(char c);
int		ft_astlen(t_ast *ast);
t_ast *ft_astindex(t_ast *ast, int idx);
void free_pinfo(t_var *var);

#endif
