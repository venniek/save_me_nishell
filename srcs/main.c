/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naykim <naykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:49:26 by naykim            #+#    #+#             */
/*   Updated: 2022/01/21 21:30:18 by naykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	g_exitcode;

void	sighandler_sigint(int signo)
{
	int status;

	// waitpid(0, &status, 0);
	printf("status in signal: %d\n", status);
	if (status != 0)
		printf("^C\n");
	g_exitcode = 1;
	printf("\n"); // Move to a new line
	rl_replace_line("", 0); // Clear the previous text
	rl_on_new_line(); // Regenerate the prompt on a newline
	rl_redisplay();
}

void	sighandler_sigquit(int signo)
{
	printf("\n"); // Move to a new line
	rl_replace_line("", 0); // Clear the previous text
	rl_on_new_line(); // Regenerate the prompt on a newline
	rl_redisplay();
}

void	start_main(t_var *var)
{
	int		ret;

	while (1)
	{
		printf("exitcode = %d\n", g_exitcode);
		ret = get_ast(var);
		if (ret == 1)
			break ;
		else if (ret == 2)
			continue ;
		if (var->ast_len == 1)
		{
			only_one_command(var);
			continue ;
		}
		init_pinfo(var);
		make_pipe_and_child(var);
		if (var->pinfo->child_pid != 0)
		{
			if (parent_process(var) == 1)
				continue ;
		}
		child_process(var);
	}
}

int	main(int ac, char **av, char **env)
{
	t_var	var;

	init_var(&var, env);
	signal(SIGQUIT, sighandler_sigquit);
	signal(SIGINT, sighandler_sigint);
	start_main(&var);
	b_exit(&var, 0);
}
