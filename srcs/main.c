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

// void	cmd_check(t_var *var, char **cmd)
// {
// 	int	i;
// 	int	okay;

// 	i = -1;
// 	okay = 0;
// 	while (var->paths[++i])
// 	{
// 		find_cmd(var, i, &cmd[0], &okay);
// 		if (okay == 1)
// 			break ;
// 	}
// 	if (okay == 0)
// 	{
// 		write(STDERR_FILENO, "bash: ", 7);
// 		write(STDERR_FILENO, cmd[0], ft_strlen(cmd[0]));
// 		write(STDERR_FILENO, ": command not found\n", 21);
// 		ft_exit(127, var);
// 	}
// }



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
	else
		b_exec(var, ptr);
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
		input = parser(read, var.our_env);
		var.ast = input;
		ptr = var.ast;
		while (ptr != NULL) {
			run_func(&var, ptr);
			ptr = ptr->next;
			printf("-----------------------\n");
		}
		free(read);
		read = 0;
		free_ast(var.ast); 
		var.ast = 0;
	}
	b_exit(&var);
}