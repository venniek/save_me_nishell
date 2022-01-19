#include "../header/minishell.h"

void *excep_malloc(int leng)
{
	void	*result;

	result = malloc(leng);
	if (result == NULL) 
		err_malloc();
	return (result);
}

void *excep_calloc(size_t count, size_t size)
{
	void	*result;

	result = ft_calloc(count, size);
	if (result == NULL)
		err_malloc();
	return (result);
}

size_t ft_sstrlen(char **strstr)
{
	size_t leng;

	leng = 0;
	if (!strstr)
		return (0);
	while (strstr[leng] != NULL)
		++leng;
	return (leng);
}

char	**ft_addonestring(char **origin, char *newline)
{
	char	**new;
	int		idxlen;
	int		i;

	idxlen = 0;
	while (origin[idxlen])
		idxlen++;
	new = (char **)malloc(sizeof(char *) * (idxlen + 2));
	i = -1;
	while (++i < idxlen)
		new[i] = origin[i];
	new[idxlen] = ft_strdup(newline);
	new[idxlen + 1] = NULL;
	idxlen = 0;
	free(origin);
	return (new);
}

char	**init_sstr(void)
{
	char	**result;

	result = (char **) excep_malloc(sizeof(char *) * 1);
	result[0] = NULL;
	return (result);
}

char	**sstrncat(char **origin, char *newline, int n)
{
	int		idx;
	int		idx_newline;
	int		len_str;
	char	*temp;
	char	*ptr_str;

	if (n < 0)
		return ft_addonestring(origin, newline);
	if (ft_sstrlen(origin) == 0)
		origin = ft_addonestring(origin, "");
	ptr_str = origin[ft_sstrlen(origin) - 1];
	if (n > ft_strlen(newline))
		n = ft_strlen(newline);
	len_str = ft_strlen(ptr_str);
	temp = excep_malloc(len_str + n + 1);
	idx = 0;
	while (idx < len_str) {
		temp[idx] = ptr_str[idx];
		++idx;
	}
	idx_newline = 0;
	while (idx < len_str + n)
		temp[idx++] = newline[idx_newline++];
	temp[len_str + n] = '\0';
	origin[ft_sstrlen(origin) - 1] = temp;
	free(ptr_str);
	return origin;
}

void	free_ast_in_var(t_var *var)
{
	if (!var)
		return ;
	free_ast(var->ast);
	var->ast = 0;
}

void	free_ast(t_ast *ast)
{
	t_ast *next_node;

	while (ast)
	{
		next_node = ast->next;
		if (ast->text)
			free_sstr(ast->text);
		if (ast->rd_owrite)
			free_sstr(ast->rd_owrite);
		if (ast->rd_append)
			free_sstr(ast->rd_append);
		if (ast->rd_input)
			free_sstr(ast->rd_input);
		if (ast->heredoc)
			free_sstr(ast->heredoc);
		free(ast);
		ast = next_node;
	}
}
void	free_sstr(char **sstr)
{
	int	i;
	int	sstr_len;

	i = 0;
	if (!sstr)
		return ;
	while (sstr[i])
	{
		free(sstr[i]);
		sstr[i] = 0;
		i++;
	}
	if (sstr)
		free(sstr);
	sstr = 0;
}

void	call_pwd(t_var *var)
{
	char *str;
	char *tmp_str;

	if (var->pwd_now)
		free(var->pwd_now);
	str = getcwd(0, 100);
	tmp_str = ft_strdup(ft_strrchr(str, '/'));
	free(str);
	str = ft_substr(tmp_str, 1, ft_strlen(tmp_str) - 1);
	free(tmp_str);
	tmp_str = ft_strjoin(str, "$ ");
	var->pwd_now = ft_strjoin("minishell-", tmp_str);
	free(str);
	str = 0;
	free(tmp_str);
	tmp_str = 0;
}

char *lookup_value(char *start, size_t leng, char **env)
{
	size_t 	idx;
	char	*temp;
	char 	*result;

	idx = 0;
	result = NULL;
	temp = ft_strndup(start, leng);
	while (env[idx] != NULL)
	{
		if (ft_strncmp(env[idx], temp, ft_strlen(temp)) == 0)
		{
			if (env[idx][ft_strlen(temp)] == '=')
			{
				result = ft_strdup(&env[idx][ft_strlen(temp) + 1]);
				break ;
			}
		}
		++idx;
	}
	free(temp);
	return (result);
}

int ft_isWhite(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	ft_astlen(t_ast *ast)
{
	int	len;

	len = 0;
	while (ast)
	{
		ast = ast->next;
		len++;
	}
	return (len);
}

t_ast *ft_astindex(t_ast *ast, int idx)
{
	t_ast *ret;

	ret = ast;
	while (idx-- > 0)
		ret = ret->next;
	return (ret);
}

void free_pinfo(t_var *var)
{
	if (!var->pinfo)
		return ;
	for (int i = 0; i < var->pinfo->num_fds; i++)
	{
		if (var->pinfo->fds[i])
		{
			free(var->pinfo->fds[i]);
			var->pinfo->fds[i] = 0;
		}
	}
	if (var->pinfo->fds)
	{
		free(var->pinfo->fds);
		var->pinfo->fds = 0;
	}
	if (var->pinfo)
	{
		free(var->pinfo);
		var->pinfo = 0;
	}
}