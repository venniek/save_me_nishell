#include "../header/minishell.h"

void sighandler_sigint(int signo) {
	printf("\n"); // Move to a new line
    rl_replace_line("", 0); // Clear the previous text
	rl_on_new_line(); // Regenerate the prompt on a newline
    rl_redisplay();
}

int main(int ac, char **av, char **PATH) {
	char *read;

	signal(SIGQUIT, sighandler_sigint);
	signal(SIGINT, sighandler_sigint);

	while (1) {
		
		read = readline("Test_Shell> ");
		if (read == NULL)
			break ;
		printf("input : %s\n", read);
		free(read);
	}
}