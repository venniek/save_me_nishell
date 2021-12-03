#include "../header/minishell.h"

int main() {
	char *read;
	while (1) {
		read = readline("Test_Shell> ");
		if (ft_strncmp(read, "q", 2) == 0)
			break ;
		printf("input : %s\n", read);
		free(read);
	}
}