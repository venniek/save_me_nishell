/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:49:26 by naykim            #+#    #+#             */
/*   Updated: 2022/01/21 15:13:30 by gyeon            ###   ########.fr       */
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
	int 	in_out[2];

	in_out[0] = dup(STDIN_FILENO);
	in_out[1] = dup(STDOUT_FILENO);
	while (1)
	{
		ret = get_ast(var);
		if (ret == 1)
			break ;
		else if (ret == 2)
			continue ;
		if (setnget_heredoc(var->ast) == 0)
			printf("!!!!!heredoc error!!!!!\n");
		dup2(in_out[0], STDIN_FILENO);
		dup2(in_out[1], STDOUT_FILENO);
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
