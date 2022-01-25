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
# include <fcntl.h>
# include <dirent.h>
# include "defines.h"
# include "../libft/libft.h"

/*
 * rd_owrite	: >	 R
 * rd_append	: >> r
 * rd_input 	: <  L
 * heredoc		: << l
 */
typedef struct s_ast
{
	char			**text;
	char			**rd_owrite;
	char			**rd_append;
	char			**rd_input;
	char			**heredoc;
	char			last_out;
	char			last_in;
	struct s_ast	*next;
}	t_ast;

typedef struct s_pipeinfo
{
	int	cnt;
	int	child_pid;
	int	num_fds;
	int	**fds;
}	t_pipeinfo;

typedef struct s_var
{
	char		*pwd_now;
	char		**our_env;
	int			ast_len;
	int			exitcode;
	t_ast		*ast;
	t_pipeinfo	*pinfo;
}	t_var;

typedef struct s_parsing
{
	char	where;
	t_ast	*result;
	char	*act;
	char	*buffer;
	char	state;
	size_t	slide;
}	t_parsing;

//=================Parser=================//
t_ast	*parser(char *line, char **env);

//=============Action_desider=============//
char	**ft_addonestring(char **origin, char *newline);
size_t	dollar_dollarquestion(const char *str);
size_t	if_flg_singlequote(char *flgs);
size_t	get_actindex(const char *str, const char state);
size_t	decide_actset(char flg);
int		rev_flg(char *flgs, char flg);

//================Actions================//
void	action_idx(char **line, size_t *slide);
char	*action_cat(char *dst, char *src, size_t slide);
char	*action_env(char *dst, char *src, char **env, size_t slide);
char	action_addonestring(t_parsing *ps);
void	action_white(char **line,	t_parsing *ps);
void	action_err(t_parsing *ps);
char	action_appendlist(t_parsing *ps);
char	action_fin(char *buffer);

//==============Redirection==============//
int		redirections(t_ast *ast);
int		setnget_heredoc(t_ast *ast);

//==========Parse_error_check==========//
t_ast	*check_result(t_ast *result);

//================Utils================//
t_ast	*init_ast(void);
void	add_ast(t_ast *front);
t_ast	*get_last(t_ast	*start);
char	*lookup_value(char *start, size_t leng, char **env);
char	*malloc_n_lcat(char *dst, char *src, size_t leng);

//================b_exec===================//
int		find_cmd(char **path, int i, char **cmd, char **env);
char	**make_paths(char **env);
void	find_and_run_command(char **cmds, char **env);
void	b_exec(t_var *var, char **cmds);
void	b_exec_with_fork(t_var *var, char **cmds);

//================b_export===================//
void	b_export(t_var *var, char **cmd);
void	print_sorted_env(char **sorted_env);
void	ft_export(t_var *var, char *new);

//================b_others===================//
void	b_env(t_var *var);
void	b_cd(t_var *var, t_ast *ptr);
void	b_pwd(void);
void	b_echo(char **cmd);
int		b_exit(t_var *var, int i);

//================b_unset===================//
int		find_remove_str(char **origin, char *remove, int len);
char	**ft_removeonestring(char **origin, char *remove, int origin_len);
void	b_unset(t_var *var, char **cmd);

//================main===================//
void	sighandler_sigint(int signo);
void	sighandler_sigquit(int signo);
void	start_main(t_var *var);

//================run_command===================//
void	run_func(t_var *var, t_ast *ptr, int flag);
void	only_one_command(t_var *var);
int		have_argument(t_var *var, char **cmds);

//================pipe_and_process===================//
void	child_process(t_var *var);
int		parent_process(t_var *var);
void	make_pipe_and_child(t_var *var);

//================utils_free===================//
void	free_sstr(char **sstr);
void	free_ast(t_ast *ast);
void	free_ast_in_var(t_var *var);
void	free_pinfo(t_var *var);

//================utils_init===================//
void	init_var(t_var *var, char **env);
char	**init_sstr(void);
void	init_pinfo(t_var *var);

//================utils_other===================//
void	*excep_malloc(int leng);
void	*excep_calloc(size_t count, size_t size);
void	call_pwd(t_var *var);
void	printf_err(char *str);
int		input_home_in_cd(t_var *var, t_ast *ptr);

//==============utils_err_handler===============//
int		if_have_slash(char **cmd);

//====================utils_ast===============//
int		get_ast(t_var *var);
int		ft_astlen(t_ast *ast);
t_ast	*ft_astindex(t_ast *ast, int idx);

//================utils_parsing===================//
int		ft_isWhite(char c);
char	*lookup_value(char *start, size_t leng, char **env);

//================utils_remove===================//
void	prt_sstr(char **sstr);
void	prt_allast(t_ast *ast);

//================utils_string===================//
size_t	ft_sstrlen(char **strstr);
char	**ft_addonestring(char **origin, char *newline);
char	**ft_sstrncat(char **origin, char *newline, int n);
char	**ft_sstrdup(char **origin);
void	echo_n_flag(char **cmd, size_t *idx, int *n_option);

#endif
