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
	t_var var;
	char *cmd_echo[5] = {"echo", "echotest", "test for echo", "last echo"};
	char *cmd_export[5] = {"export", "a=3", "b=", "c"};
	char *cmd_unset[4] = {"unset", "b=", "c"};
	char *cmd_cd[3] = {"cd"};
	var.ast = 0;
	var.our_env = ft_sstrdup(env);
	var.pwd_now = 0;

	printf("-----pwd----\n");
	b_pwd();
	printf("\n-----env----\n");
	b_env(var.our_env);
	printf("\n-----echo----\n");
	b_echo(cmd_echo);
	printf("\n-----export----\n");
	b_export(&var, cmd_export);
	b_env(var.our_env);
	printf("\n-----unset----\n");
	b_unset(&var, cmd_unset);
	b_env(var.our_env);
	printf("-----cd----\n");
	b_cd(&var, cmd_cd);
	b_pwd();
	printf("------exit--------\n");
	b_exit(&var);

	return 0;
}