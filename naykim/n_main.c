#include "../header/minishell.h"

// void	sighandler_sigint(int signo) {
// 	printf("\n"); // Move to a new line
// 	rl_replace_line("", 0); // Clear the previous text
// 	rl_on_new_line(); // Regenerate the prompt on a newline
// 	rl_redisplay();
// }

size_t ft_sstrlen(char **strstr) {
	size_t leng;

	leng = 0;
	while (strstr[leng] != NULL)
		++leng;
	return (leng);
}

char	**ft_addonestring(char **origin, char *newline)
{
	char	**new;
	int		idxlen;
	int		i;

	idxlen = ft_sstrlen(origin);
	new = (char **)malloc(sizeof(char *) * (idxlen + 2));
	i = -1;
	while (++i < idxlen)
		new[i] = ft_strdup(origin[i]);
	new[idxlen] = ft_strdup(newline);
	new[idxlen + 1] = NULL;
	i = -1;
	while (++i < idxlen)
		free(origin[i]);
	free(origin);
	return (new);
}


int	main(int argc, char **argv, char **env) {
	char	*read;
	char **our_env;
// //	t_ast	*input;

// 	signal(SIGINT, sighandler_sigint);
// 	signal(SIGQUIT, sighandler_sigint);
	argc = 10;
	argv = 0;
	our_env = (char **)malloc(sizeof(char *) * (ft_sstrlen(env) + 1));
	for (int i = 0; i < ft_sstrlen(env); i++)
		our_env[i] = ft_strdup(env[i]);
	our_env[ft_sstrlen(env)] = 0;
	while (1) {
		read = readline("Test_Shell> ");
		if (read == NULL)
			break ;
		printf("input : %s\n", read);
		if (!ft_strncmp(read, "env", 3))
			b_env(our_env);
		else if (!ft_strncmp(read, "pwd", 3))
			b_pwd();
		else if (!ft_strncmp(read, "cd", 2))
			b_cd(ft_substr(read, 3, ft_strlen(read) - 3));
		else if (!ft_strncmp(read, "export", 6))  // 함수 안에서 반복문 돌리기
			b_export(&our_env, ft_substr(read, 7, ft_strlen(read) - 7));
		else if (!ft_strncmp(read, "unset", 5))
			our_env = b_unset(our_env, ft_substr(read, 6, ft_strlen(read) - 6));
		else if (!ft_strncmp(read, "echo", 4))
			b_echo(ft_substr(read, 5, ft_strlen(read) - 5)); // char* -> char** 고치기
		else if (!ft_strncmp(read, "exit", 4))
			b_exit();
		printf("------after one command--------\n");
		free(read);
	}
}