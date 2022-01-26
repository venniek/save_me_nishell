/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:19:09 by gyeon             #+#    #+#             */
/*   Updated: 2022/01/26 15:19:10 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	g_exitcode;

void	sighandler_sigint(int signo)
{
	pid_t	result;

	g_exitcode = 1;
	result = waitpid(-1, NULL, WNOHANG);
	if (result < 0 && errno != 10)
		exit(printf_err("fatal: critical error occured in process.\n"));
	else if (result != 0)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	signo = 0;
}

void	sighandler_sigquit(int signo)
{
	pid_t	result;

	result = waitpid(-1, NULL, WNOHANG);
	if (result < 0 && errno != 10)
		exit(printf_err("fatal: critical error occured in process.\n"));
	else if (result < 0)
	{
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
			exit(printf_err("fatal: can't dup STDIN\n"));
		in_out[1] = dup(STDOUT_FILENO);
		if (in_out[1] < 0)
			exit(printf_err("fatal: can't dup STDOUT\n"));
		first = 1;
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (dup2(in_out[0], STDIN_FILENO) < 0)
		exit(printf_err("fatal: can't dup from STDIN\n"));
	if (dup2(in_out[1], STDOUT_FILENO) < 0)
		exit(printf_err("fatal: can't dup from STDOUT\n"));
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
		if (setnget_heredoc(var->ast) == 1)
			continue ;
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
		return (printf_err("No argument required\n"));
	av = 0;
	init_var(&var, env);
	signal(SIGINT, sighandler_sigint);
	signal(SIGQUIT, sighandler_sigquit);
	start_main(&var);
	b_exit(&var, 0);
}
