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
		b_cd(var, cmds);
	else if (!ft_strncmp(cmd, "pwd", 3))
		b_pwd();
	else if (!ft_strncmp(cmd, "env", 3))
		b_env(var->our_env);
	else if (!ft_strncmp(cmd, "echo", 4))
		b_echo(cmds);
	else if (!ft_strncmp(cmd, "export", 6))
		b_export(var, cmds);
	else if (!ft_strncmp(cmd, "unset", 5))
		b_unset(var, cmds);
	else if (!ft_strncmp(cmd, "exit", 4))
		b_exit(var);
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
		read = readline(ft_strjoin(, ">  "));
		if (read == NULL)
			break ;
		input = parser(read, env);
		var.ast = input;
		ptr = input;
		while (ptr != NULL) {
			run_func(&var, ptr);
			ptr = ptr->next;
			printf("-----------------------\n");
		}
		free(read);
		read = 0;
	}
}