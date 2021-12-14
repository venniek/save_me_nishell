#include "../header/minishell.h"

void ft_sighandler(int sig)
{
	rl_replace_line();
}

int main(int ac, char **av, char **env)
{
	char *line;
	char **envs; // 구조체에 넣기?
	char *read;
	int tmp;
	int fd;

	signal(SIGINT, ft_sighandler);
	int i = 0;
	envs = (char **)malloc(sizeof(char *) * 100);  //크기를 몇으로 해야하지???
	while ((tmp = get_next_line(fd, &line)))
	{
		envs[i] = ft_strdup(line);
		free(line);
		i++;
	}
	while (1) {
		read = readline("Test_Shell> "); // 여기서 gnl을 써야하나???
		if (strncmp(read, "q", 2) == 0)
			break ;
		// token();
		// parsing();

		free(read);
	}
	return 0;
}
