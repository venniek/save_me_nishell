/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naykim <naykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:49:26 by naykim            #+#    #+#             */
/*   Updated: 2022/01/20 16:26:02 by naykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	sighandler_sigint(int signo)
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
	signal(SIGQUIT, sighandler_sigint);
	signal(SIGINT, sighandler_sigint);
	start_main(&var);
	b_exit(&var, 0);
}
