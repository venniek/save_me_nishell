#include "../header/minishell.h"

void	sighandler_sigint(int signo) {
	printf("\n"); // Move to a new line
	rl_replace_line("", 0); // Clear the previous text
	rl_on_new_line(); // Regenerate the prompt on a newline
	rl_redisplay();
}

void init_var(t_var *var, char **env)
{
	var->ast = 0;
	var->ast_len = 0;
	var->our_env = ft_sstrdup(env);
	var->pwd_now = 0;
	var->pinfo = 0;
}

void init_pinfo(t_var *var)
{
	int	i;

	var->pinfo = (t_pipeinfo *)malloc(sizeof(t_pipeinfo) * 1);
	var->pinfo->cnt = 0;
	var->pinfo->child_pid = 0;
	var->pinfo->num_fds = var->ast_len;
	var->pinfo->fds = (int **)malloc(var->ast_len * sizeof(int *));
	if (var->pinfo->fds == NULL)
		exit(1);
	i = 0;
	while (i < var->ast_len)
	{
		var->pinfo->fds[i] = (int *)malloc(2 * sizeof(int));
		if (var->pinfo->fds[i++] == NULL)
			exit(1);
	}
}

void	prt_sstr(char **sstr)
{
	size_t	i = 0;
	if (sstr == NULL)
		return ;
	while (sstr[i] != NULL)
		printf("\t%s\n", sstr[i++]);
}

void	prt_allast(t_ast *ast)
{
	t_ast	*ptr;

	ptr = ast;
	while (ptr != NULL)
	{
		printf("[ast->text]---------\n");
		prt_sstr(ptr->text);
		printf("[ast->rd_owrite]----\n");
		prt_sstr(ptr->rd_owrite);
		printf("[ast->rd_append]----\n");
		prt_sstr(ptr->rd_append);
		printf("[ast->rd_input]-----\n");
		prt_sstr(ptr->rd_input);
		printf("[ast->heredoc]------\n");
		prt_sstr(ast->heredoc);
		ptr = ptr->next;
	}
	return ;
}

void run_func(t_var *var, t_ast *ptr)
{
	char **cmds;
	char *cmd;
	int		stat_loc;
	
	if (!ptr->text)
		return ;
	if (!ptr->text[0])
		return ;
	cmds = ptr->text;
	cmd = cmds[0];
	printf("======here start run_func. cmd: %s\n", cmd);
	// waitpid(var->pinfo->child_pid, &stat_loc, WNOHANG);
	// close(var->pinfo->fds[var->pinfo->cnt][1]);
	// dup2(var->pinfo->fds[var->pinfo->cnt][0], STDIN_FILENO);
	// dup2(var->pinfo->fds[var->pinfo->cnt - 1][1], STDOUT_FILENO);
	if (!ft_strncmp(cmd, "cd", 2))
		return b_cd(var, cmds);
	if (!ft_strncmp(cmd, "pwd", 3))
		return b_pwd();
	if (!ft_strncmp(cmd, "env", 3))
		return b_env(var->our_env);
	if (!ft_strncmp(cmd, "echo", 4))
		return b_echo(cmds);
	if (!ft_strncmp(cmd, "export", 6))
		return b_export(var, cmds);
	if (!ft_strncmp(cmd, "unset", 5))
		return b_unset(var, cmds);
	if (!ft_strncmp(cmd, "exit", 4))
		b_exit(var);
	else
		b_exec(var, cmds);

}

int	main(int ac, char **av, char **env) {
	char	*read;
	t_ast	*input;
	t_var	var;

	init_var(&var, env);
	signal(SIGQUIT, sighandler_sigint);
	signal(SIGINT, sighandler_sigint);

	while (1) {
		call_pwd(&var);
		read = readline(var.pwd_now);
		if (read == NULL)
		{
			printf("let's break\n");
			break ;
		}
		input = parser(read, env);
		free(read);
		read = NULL;
		if (input == NULL)
		{
			write(1, "plz close quotes.\n", 18);
			continue ;
		}
		// prt_allast(input);
		var.ast = input;
		var.ast_len = ft_astlen(var.ast);
		if (!var.ast->text[0])
		{
			printf("no cmd. just new line\n");
			free_ast(var.ast);
			continue;
		}
		init_pinfo(&var);
		if (var.ast_len == 1)
		{
			printf("here is just one ast\n");
			run_func(&var, var.ast);
			printf("--------------------------------\n");
			free_ast(var.ast);
			free_pinfo(&var);
			continue ;
		}
		while (var.pinfo->cnt < var.ast_len)
		{
			if (pipe(var.pinfo->fds[var.pinfo->cnt]) == -1)
				return (1);
			var.pinfo->child_pid = fork();
			if (var.pinfo->child_pid == -1)
				return (1);
			else if (var.pinfo->child_pid != 0)
				break ;
			++(var.pinfo->cnt);
		}
		if (var.pinfo->child_pid != 0)
		{
			int	i;
			int	stat_loc;

			if (var.pinfo->cnt == 0)
			{
				waitpid(var.pinfo->child_pid, &stat_loc, 0);
				printf("======this is the very first parent======\n");
				free_ast(var.ast);
				var.ast = 0;
				i = 1;
				close(var.pinfo->fds[0][0]);
				close(var.pinfo->fds[0][1]);
				while (i < var.pinfo->num_fds)
					close(var.pinfo->fds[i++][0]);
				// free_pinfo(&var);
			}
			else
			{
				waitpid(var.pinfo->child_pid, &stat_loc, 0);
				printf("===here is parent after waiting child\n");
			}
			if (WEXITSTATUS(stat_loc) != 0)
				exit(WEXITSTATUS(stat_loc));
			else
			{
				if (var.pinfo->cnt == 0)
				{
					free_pinfo(&var);
					continue;
				}
			}
		}
		run_func(&var, ft_astindex(var.ast, var.pinfo->num_fds - var.pinfo->cnt));
		printf("--------------------------------\n");
		free_pinfo(&var);
		printf("before exit number %d process\n", var.pinfo->cnt);
		// exit(0);
	}
	printf("before last b_exit\n");
	b_exit(&var);
}
