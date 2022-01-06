#include "../header/minishell.h"

// 일단... ;별로 나눠서 모두 char**형채로 저장하는


void	sighandler_sigint(int signo) {
	printf("\n"); // Move to a new line
	rl_replace_line("", 0); // Clear the previous text
	rl_on_new_line(); // Regenerate the prompt on a newline
	rl_redisplay();
}

int	main(int ac, char **av, char **env) {
	char	*read;
	t_ast	*input;
	t_ast	*ptr;

	signal(SIGQUIT, sighandler_sigint);
	signal(SIGINT, sighandler_sigint);

	while (1) {
		read = readline("Test_Shell> ");
		if (read == NULL)
			break ;
		// printf("input : %s\n", read);
		input = paser(read, env);
		ptr = input;
		int cnt = 0;
		while (ptr != NULL) {
			int i = 0;
			printf("-------[%d list]-------\n", cnt);
			while (ptr->text[i] != NULL) {
				printf("%s\n", ptr->text[i]);
				free(ptr->text[i++]);
			}
			t_ast *temp;
			temp = ptr;
			ptr = ptr->next;
			free(temp);
			printf("-----------------------\n");
			cnt++;
		}
		free(read);
	}
}