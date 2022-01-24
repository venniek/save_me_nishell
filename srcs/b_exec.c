/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naykim <naykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:49:22 by naykim            #+#    #+#             */
/*   Updated: 2022/01/24 15:22:43 by naykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

extern int	g_exitcode;

char	**make_paths(char **env)
{
	int		i;
	int		tmp;
	char	*tmpenv;
	char	**path;

	tmpenv = 0;
	path = 0;
	i = -1;
	while (env[++i])
	{
		tmp = ft_strncmp(ft_substr(env[i], 0, 5), "PATH=", 5);
		if (tmp == 0)
		{
			tmpenv = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
			path = ft_split(tmpenv, ':');
			break ;
		}
	}
	if (tmpenv)
		free(tmpenv);
	return (path);
}

void	find_cmd(char **path, int i, char **cmd, char **env)
{
	char	*tmp;
	char	**tmpcmd;

	execve(cmd[0], cmd, env);
	tmpcmd = ft_sstrdup(cmd);
	tmp = ft_strjoin(path[i], "/");
	free(tmpcmd[0]);
	tmpcmd[0] = ft_strjoin(tmp, cmd[0]);
	execve(tmpcmd[0], tmpcmd, env);
	free(tmp);
	tmp = 0;
	free_sstr(tmpcmd);
	tmpcmd = 0;
}

void	find_and_run_command(char **cmds, char **env)
{
	int		i;
	char	**path;

	path = make_paths(env);
	i = -1;
	while (++i < ft_sstrlen(path))
		find_cmd(path, i, cmds, env);
	free_sstr(path);
}

void	b_exec(t_var *var, char **cmds)
{
	g_exitcode = 0;
	find_and_run_command(cmds, var->our_env);
	printf_err("minishell: ");
	printf_err(cmds[0]);
	if (ft_strchr(cmds[0], '/'))
		printf_err(": No such file or directory\n");
	else
		printf_err(": command not found\n");
	g_exitcode = 127;
	b_exit(var, 127);
}

void	b_exec_with_fork(t_var *var, char **cmds)
{
	int		pid;
	int		status;
	int		signum;

	pid = fork();
	if (pid == 0)
		b_exec(var, cmds);
	else
	{
		waitpid(pid, &status, 0);
		g_exitcode = WEXITSTATUS(status);
		signum = WTERMSIG(status);
		if (signum != 0)
		{
			if (signum == 2)
				printf("^C\n");
			g_exitcode = 128 + WTERMSIG(status);
		}
	}
}
