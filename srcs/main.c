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
	var->our_env = ft_sstrdup(env);
	var->pwd_now = 0;
}

void run_func(t_var *var, t_ast *ptr)
{
	char **cmds = ptr->text;
	char *cmd = cmds[0];

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
	t_ast	*ptr;
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
		ptr = var.ast;
		while (ptr != NULL) {
			run_func(&var, ptr);
			ptr = ptr->next;
			printf("-----------------------\n");
		}
		free_ast(var.ast);
		var.ast = 0;
	}
	b_exit(&var);
}
