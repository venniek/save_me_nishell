#include "../header/minishell.h"

char	**make_paths(char **env)
{
	int		i;
	int		tmp;
	char	*tmpenv;
	char	**path;

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
	free(tmpenv);
	return (path);
}

void	find_cmd(char **path, int i, char **cmd, char **env, int *okay)
{
	char	*tmp;
	char	**tmpcmd;
	int ret;

	ret = execve(cmd[0], cmd, env);
	printf("ret: %d\n", ret);
	// if (execve(cmd[0], cmd, env) < 0)
	// {

	// 	printf("success! %s\n", tmpcmd[0]);
	// 	*okay = 1;
	// 	return ;
	// }
	// tmpcmd = ft_sstrdup(cmd);
	// tmp = ft_strjoin(path[i], "/");
	// free(tmpcmd[0]);
	// tmpcmd[0] = ft_strjoin(tmp, cmd[0]);
	// printf("tmpcmd[0]: %s\n", tmpcmd[0]);
	// if (execve(tmpcmd[0], tmpcmd, env) != -1)
	// {
	// 	printf("success! %s\n", tmpcmd[0]);
	// 	*okay = 1;
	// }
	// free(tmp);
	// tmp = 0;
	// free_sstr(tmpcmd);
	// tmpcmd = 0;
}

int run_command(char **cmds, char **env, int *okay)
{
	int		i;
	char	**path;
	int pid;
	int status;

	path = make_paths(env);
	*okay = 0;
	i = -1;
	while (++i < ft_sstrlen(path))
	{
		pid = fork();
		if (pid == 0)
		{
			find_cmd(path, i, cmds, env, okay);

		}
		else {
			waitpid(pid, &status, 0);
		}
		printf("okay: %d\n", *okay);
	
		if (*okay == 1)
			break ;
	}
	free_sstr(path);
	if (*okay == 1)
		return (1);
	return (0);
}


void b_exec(t_var *var, char **cmds)
{
	int		pid;
	int		status;
	int *okay;

	*okay = 0;
	printf("cmds[0]: %s\n", cmds[0]);
	// pid = fork();
	// if (pid == 0)
	// {
	// 	if (run_command(cmds, var->our_env, okay) == 0)
	// 	{
	// 		printf("run command end\n");
	// 		// 실패 에러문
	// 		exit(126); // ?? 126 맞나?
	// 	}
	// }
	// else
	// 	waitpid(pid, &status, 0);
	// printf("after waitpid, okay = %d\n", *okay);
}