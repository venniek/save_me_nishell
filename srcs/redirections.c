/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 21:29:22 by gyeon             #+#    #+#             */
/*   Updated: 2022/01/25 21:47:56 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*strcat_num(char *dst, int num)
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

void	readline_heredoc(int temp_fd, char *delimiter)
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
	int			temp_fd;
	char		*delimiter;

	ptr = ast;
	while (ptr != NULL)
	{
		cnt = 0;
		while (ptr->heredoc[cnt] != NULL)
		{
			delimiter = ptr->heredoc[cnt];
			ptr->heredoc[cnt] = strcat_num(".doc", cnt);
			temp_fd
				= open(ptr->heredoc[cnt], O_WRONLY | O_TRUNC | O_CREAT, 0666);
			if (temp_fd < 0)
				return (0);
			readline_heredoc(temp_fd, delimiter);
			++cnt;
		}
		ptr = ptr->next;
	}
	return (1);
}

/*
 *  0 heredoc << l
 *  1 append >> r
 *  2 input < L
 *  3 owrite > R
 */
int	open_files(size_t rd, char **file)
{
	int		temp_fd;
	size_t	idx;
	size_t	len_sstr;

	idx = 0;
	len_sstr = ft_sstrlen(file);
	while (idx < len_sstr)
	{
		if (rd == 1)
			temp_fd = open(file[idx], O_WRONLY | O_APPEND | O_CREAT, 0666);
		else if (rd == 2)
			temp_fd = open(file[idx], O_RDONLY);
		else
			temp_fd = open(file[idx], O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (temp_fd < 0)
		{
			printf_err("minishell: ");
			printf_err(file[idx]);
			printf_err(": No such file or directory\n");
			return (0);
		}
		close(temp_fd);
		idx++;
	}
	return (1);
}

int	redirections(t_ast *ast)
{
	size_t	rd;
	int		ttt;
	char	**ptr[4];

	rd = 1;
	ptr[0] = ast->heredoc;
	ptr[1] = ast->rd_append;
	ptr[2] = ast->rd_input;
	ptr[3] = ast->rd_owrite;
	while (rd++ < 4)
		if (open_files(rd - 1, ptr[rd - 1]) == 0)
			return (0);
	if (ast->last_in == 'l')
		dup2(open(ptr[0][ft_sstrlen(ptr[0]) - 1], O_RDONLY), STDIN_FILENO);
	else if (ast->last_in == 'L')
		dup2(open(ptr[2][ft_sstrlen(ptr[2]) - 1], O_RDONLY), STDIN_FILENO);
	if (ast->last_out == 'r')
		dup2(open(ptr[1][ft_sstrlen(ptr[1]) - 1], APPEND, 0666), STDOUT_FILENO);
	else if (ast->last_out == 'R')
	{
		ttt = open(ptr[3][ft_sstrlen(ptr[3]) - 1], OWRITE, 0666);
		dup2(ttt, STDOUT_FILENO);
		close(ttt);
	}
	rd = 0;
	return (1);
}
