#include "../header/minishell.h"

void	sighandler_sigint(int signo) {
	printf("\n"); // Move to a new line
	rl_replace_line("", 0); // Clear the previous text
	rl_on_new_line(); // Regenerate the prompt on a newline
	rl_redisplay();
}

int	main(int ac, char **av, char **env) {
	char	*read;
	t_ast	*input;

	signal(SIGINT, sighandler_sigint);
	signal(SIGQUIT, sighandler_sigint);

	while (1) {
		read = readline("Test_Shell> ");
		if (read == NULL)
			break ;
		printf("input : %s\n", read);
		// if (!ft_strncmp(read, "echo", 5))
		// 	b_echo("echo test");
		// else if (!ft_strncmp(read, "cd", 3))
		// 	b_cd("..");
		// else if (!ft_strncmp(read, "env", 4))
		// 	b_env(env);
		// else if (!ft_strncmp(read, "exit", 5))
		// 	b_exit();
		// else if (!ft_strncmp(read, "export", 7))
		// {
		// 	b_export(env, "ADD=add something");
		// }
		// else if (!ft_strncmp(read, "unset", 6))
		// 	b_unset(env, "ADD");
		// else if (!ft_strncmp(read, "pwd", 4))
		// 	b_pwd();
		free(read);
	}
}