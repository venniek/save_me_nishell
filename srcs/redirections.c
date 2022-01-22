#include "../header/minishell.h"

// 0: 연결 x, 

char		*strcat_num(char *dst, int num)
{
	size_t	idx;	
	size_t	str_len;
	size_t	digit;
	char	*result;
	int		temp_num;

	str_len = ft_strlen(dst);
	temp_num = num;
	digit = 1;
	while (temp_num > 9)
	{
		temp_num /= 10;
		++digit;
	}
	result = (char *)excep_malloc(sizeof(char) * (str_len + digit + 1));
	idx = -1;
	while (dst[++idx] != '\0')
		result[idx] = dst[idx];
	result[str_len + digit] = '\0';
	while (digit != 0)
	{
		result[str_len + --digit] = (num %= 10) + '0';
		num /= 10;
	}
	return (result);
}

void	readlein_heredoc(t_ast *ptr, int temp_fd, char *delimiter)
{
	char		*read;

	while (1)
	{
		read = readline(">");
		if (read == NULL)
			continue ;
		if (ft_strncmp(read, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(read);
			free(delimiter);
			close(temp_fd);
			break ;
		}
		else
		{
			write(temp_fd, read, ft_strlen(read));
			write(temp_fd, "\n", 1);
			free(read);
		}
	}
}

int	setnget_heredoc(t_ast *ast)
{
	t_ast		*ptr;
	int			cnt;
	int 		temp_fd;
	// char		*read;
	char 		*delimiter;

	ptr = ast;
	while (ptr != NULL)
	{
		cnt = 0;
		while (ptr->heredoc[cnt] != NULL)
		{
			delimiter = ptr->heredoc[cnt];
			ptr->heredoc[cnt] = strcat_num(".dc", cnt);
			temp_fd = open(ptr->heredoc[cnt], O_WRONLY | O_TRUNC | O_CREAT, 0666);
			if (temp_fd < 0)
				return (0);
			readlein_heredoc(ptr, temp_fd, delimiter);
			// while (1)
			// {
			// 	read = readline(">");
			// 	if (read == NULL)
			// 		continue ;
			// 	if (ft_strncmp(read, delimiter, ft_strlen(ptr->heredoc[cnt])) == 0)
			// 	{
			// 		free(read);
			// 		free(delimiter);
			// 		close(temp_fd);
			// 		break ;
			// 	}
			// 	else
			// 	{
			// 		write(temp_fd, read, ft_strlen(read));
			// 		write(temp_fd, "\n", 1);
			// 		free(read);
			// 	}
			// }
			++cnt;
		}
		ptr = ptr->next;
	}
	return (1);
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
	int		temp_fd;

	rd = 0;
	ptr[0] = ast->heredoc;		// l <<
	ptr[1] = ast->rd_append;	// r >>
	ptr[2] = ast->rd_input;		// L <
	ptr[3] = ast->rd_owrite;	// R >
	while (rd < 4)
	{
		idx = 0;
		len_sstr = ft_sstrlen(ptr[rd]);
		//fds[rd] = (int *)excep_malloc(sizeof(int) * len_sstr);
		while (idx < len_sstr)
		{
			if (rd == 0) //heredoc 임시파일 open, << l
				//fds[rd][idx] = open(ptr[rd][idx], O_RDONLY);
				temp_fd = open(ptr[rd][idx], O_RDONLY);
			else if (rd == 1) // append >> r
				temp_fd = open(ptr[rd][idx], O_WRONLY | O_APPEND | O_CREAT, 0666);
			else if (rd == 2) // input < L
				temp_fd = open(ptr[rd][idx], O_RDONLY);
			else //rd == 3, owrite > R
				temp_fd = open(ptr[rd][idx], O_WRONLY | O_TRUNC | O_CREAT, 0666);
			if (temp_fd < 0)
			{
				printf("%s: No such file or directory\n", ptr[rd][idx]);
				return 0;
			}
			close(temp_fd);
			idx++;
		}
		rd++;
	}
	if (ast->last_in == 'l')
		dup2(open(ptr[0][ft_sstrlen(ptr[0]) - 1], O_RDONLY), STDIN_FILENO);
	else if (ast->last_in == 'L')
		dup2(open(ptr[2][ft_sstrlen(ptr[2]) - 1], O_RDONLY), STDIN_FILENO);
	if (ast->last_out == 'r')
		dup2(open(ptr[1][ft_sstrlen(ptr[1]) - 1], O_WRONLY | O_APPEND | O_CREAT, 0666), STDOUT_FILENO);
	else if (ast->last_out == 'R')
		dup2(open(ptr[3][ft_sstrlen(ptr[3]) - 1], O_WRONLY | O_TRUNC | O_CREAT, 0666), STDOUT_FILENO);
	rd = 0;
	return 1;
}
