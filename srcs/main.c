#include "../header/minishell.h"

void	sighandler_sigint(int signo) {
	printf("\n"); // Move to a new line
	rl_replace_line("", 0); // Clear the previous text
	rl_on_new_line(); // Regenerate the prompt on a newline
	rl_redisplay();
}

void only_one_command(t_var *var)
{
	run_func(var, var->ast);
	printf("--------------------------------\n");
	free_ast(var->ast);
	var->ast = 0;
}

void run_func(t_var *var, t_ast *ptr)
{
	char **cmds;
	int		stat_loc;
	
	if (!ptr->text || !ptr->text[0])
		return ;
	cmds = ptr->text;
	if (!ft_strncmp(cmds[0], "cd", 2))
		return b_cd(var, cmds);
	if (!ft_strncmp(cmds[0], "pwd", 3))
		return b_pwd();
	if (!ft_strncmp(cmds[0], "env", 3))
		return b_env(var->our_env);
	if (!ft_strncmp(cmds[0], "echo", 4))
		return b_echo(cmds);
	if (!ft_strncmp(cmds[0], "export", 6))
		return b_export(var, cmds);
	if (!ft_strncmp(cmds[0], "unset", 5))
		return b_unset(var, cmds);
	if (!ft_strncmp(cmds[0], "exit", 4))
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
			break ;
		input = parser(read, env);
		free(read);
		read = NULL;
		if (input == NULL)
		{
			write(1, "plz close quotes.\n", 18);
			continue ;
		}
		var.ast = input;
		var.ast_len = ft_astlen(var.ast);
		if (!var.ast->text[0])
		{
			free_ast(var.ast);
			var.ast = 0;
			continue;
		}
		if (var.ast_len == 1)
		{
			only_one_command(&var);
			continue ;
		}
		init_pinfo(&var);
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

			waitpid(var.pinfo->child_pid, &stat_loc, 0);
			if (var.pinfo->cnt == 0)
			{
				free_ast(var.ast);
				var.ast = 0;
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
		int now_cnt = var.pinfo->num_fds - var.pinfo->cnt;
		close(var.pinfo->fds[now_cnt][1]);
		dup2(var.pinfo->fds[now_cnt][0], STDIN_FILENO);
		dup2(var.pinfo->fds[now_cnt - 1][1], STDOUT_FILENO);
		run_func(&var, ft_astindex(var.ast, now_cnt));
		printf("--------------------------------\n");
		free_pinfo(&var);
		exit(0);
	}
	b_exit(&var);
}
