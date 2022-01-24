#include "../header/minishell.h"

int	g_exitcode;

void	sighandler_sigint(int signo)
{
	g_exitcode = 1;
	if (waitpid(-1, NULL, WNOHANG) != 0)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	signo = 0;
}

void	set_stdinout(void)
{
	static int	first = 0;
	static int	in_out[2];

	if (first == 0)
	{
		in_out[0] = dup(STDIN_FILENO);
		if (in_out[0] < 0)
			exit (0);
		in_out[1] = dup(STDOUT_FILENO);
		if (in_out[1] < 0)
			exit (0);
		first = 1;
	}
	if (dup2(in_out[0], STDIN_FILENO) < 0)
		exit (0);
	if (dup2(in_out[1], STDOUT_FILENO) < 0)
		exit (0);
}

void	start_main(t_var *var)
{
	int		ret;

	while (1)
	{
		set_stdinout();
		ret = get_ast(var);
		if (ret == 1)
			break ;
		else if (ret == 2)
			continue ;
		if (setnget_heredoc(var->ast) == 0)
			printf("!!!!!heredoc error!!!!!\n");
		if (var->ast_len == 1)
		{
			only_one_command(var);
			continue ;
		}
		init_pinfo(var);
		make_pipe_and_child(var);
		if (var->pinfo->child_pid != 0 && parent_process(var) == 1)
			continue ;
		child_process(var);
	}
}

int	main(int ac, char **av, char **env)
{
	t_var	var;

	if (ac != 1)
	{
		printf_err("No argument required\n");
		return (1);
	}
	av = 0;
	init_var(&var, env);
	signal(SIGINT, sighandler_sigint);
	signal(SIGQUIT, SIG_IGN);
	start_main(&var);
	b_exit(&var, 0);
}
