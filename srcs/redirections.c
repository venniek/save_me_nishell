#include "../header/minishell.h"

char		*strcat_num(char *dst, int num)
{
	size_t	idx;	
	size_t	str_len;
	size_t	digit;
	char	*result;
	int		temp_num;

	if (dst == NULL | num < 0)
		return (NULL);
	str_len = ft_strlen(dst);
	temp_num = num;
	digit = 1;
	while (temp_num > 9)
	{
		temp_num /= 10;
		++digit;
	}
	result = (char *)excep_malloc(sizeof(char) * (str_len + digit + 1));
	idx = 0;
	while (dst[idx] != '\0')
	{
		result[idx] = dst[idx];
		idx++;
	}
	result[str_len + digit] = '\0';
	while (digit != 0)
	{
		result[str_len + --digit] = (num %= 10) + '0';
		num /= 10;
	}
	return (result);
}

t_heredoc	*setnget_heredoc(t_ast *ast)
{
	t_ast		*ptr;
	t_heredoc	*result;
	int			cnt;
	int			heredoc_cnt;
	char		*read;

	ptr = ast;
	heredoc_cnt = 0;
	while (ptr != NULL)
	{
		heredoc_cnt += ft_sstrlen(ptr->heredoc);
		ptr = ptr->next;
	}
	if (heredoc_cnt == 0)
		return (NULL);
	result = (t_heredoc *)excep_malloc(sizeof(t_heredoc) * 1);
	result->doc_cnt = heredoc_cnt;
	result->fds = (int *)excep_malloc(sizeof(int) * heredoc_cnt);
	ptr = ast;
	while (ptr != NULL)
	{
		cnt = 0;
		while (ptr->heredoc[cnt] != NULL)
		{
			result->docs[cnt] = strcat_num(".dc", cnt);
			result->fds[cnt] = open(result->docs[cnt], O_WRONLY | O_TRUNC | O_CREAT, 0666);
			while (1)
			{
				read = readline(">");
				if (read == NULL)
					continue ;
				else if (ft_strncmp(read, ptr->heredoc[cnt], ft_strlen(read)))
					break ;
				else
					write(result->fds[cnt], read, ft_strlen(read));
			}
		}
	}
	return (result);
}

/*
 * fds : 
*/
int	redirections(t_ast *ast)
{
	size_t	rd;
	size_t	idx;
	size_t	len_sstr;
	char	**ptr[4];
	int		*fds[4];

	rd = 0;
	ptr[0] = ast->heredoc;		// l
	ptr[1] = ast->rd_append;	// r
	ptr[2] = ast->rd_input;		// R
	ptr[3] = ast->rd_owrite;	// L
	while (rd < 4)
	{
		idx = 0;
		len_sstr = ft_sstrlen(ptr[rd]);
		fds[rd] = (int *)excep_malloc(sizeof(int) * len_sstr);
		while (idx < len_sstr)
		{
			printf("%zu : %s\n", rd, ptr[rd][idx]);
			if (rd == 0) //heredoc 임시파일 open,
				;	
			else if (rd == 1) // append
				fds[rd][idx] = open(ptr[rd][idx], O_WRONLY | O_CREAT, 0666);
			else if (rd == 2) // input
				fds[rd][idx] = open(ptr[rd][idx], O_RDONLY);
			else //rd == 3, owrite
				fds[rd][idx] = open(ptr[rd][idx], O_WRONLY | O_TRUNC | O_CREAT, 0666);
			if (fds[rd][idx] < 0)
			{
				printf("%s: No such file or directory\n", ptr[rd][idx]);
				return 0;
			}
			else
				printf("%s: %d\n", ptr[rd][idx], fds[rd][idx]);
			idx++;
		}
		rd++;
	}
	if (ast->last_in == 'l')
		; //dup2(fds[0][ft_sstrlen(ptr[0])], STDIN_FILENO);
	else if (ast->last_out == 'r')
		dup2(fds[1][ft_sstrlen(ptr[1])], STDOUT_FILENO);
	else if (ast->last_out == 'R')
		dup2(fds[2][ft_sstrlen(ptr[2])], STDOUT_FILENO);
	else // L
		dup2(fds[3][ft_sstrlen(ptr[3])], STDIN_FILENO);
	while (rd < 4)
		free(fds[rd++]);
	return 1;
}