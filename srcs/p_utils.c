//
// Created by 연규준 on 2022/01/13.
//
#include "../header/minishell.h"

char	*malloc_n_lcat(char *dst, char *src, size_t leng)
{
	char	*result;
	size_t	len_dst;

	if (leng == 0)
		return (NULL);
	len_dst = ft_strlen(dst);
	if (len_dst > leng)
		return (NULL);
	result = (char *) excep_malloc(leng);
	result[0] = '\0';
	ft_strlcat(result, dst, len_dst + 1);
	ft_strlcat(result, src, leng);
	return (result);
}

t_ast	*get_last(t_ast	*start)
{
	while (start->next != NULL)
		start = start->next;
	return (start);
}

// 새 ast를 init하고, 그것을 반환
// result->next = NULL;초기화 안해줘서 한참 해맸음.
// 다음에 해당 주소를 다시 사용할수 있기 때문에, 한상 NULL로 초기화해주는 습관을 가지자...
t_ast	*init_ast(void)
{
	t_ast	*result;

	result = (t_ast *) excep_malloc(sizeof(t_ast));
	result->text = init_sstr();
	result->next = NULL;
	result->rd_owrite = init_sstr();
	result->rd_append = init_sstr();
	result->rd_input = init_sstr();
	result->heredoc = init_sstr();
	result->last_out = 0;
	result->last_in = 0;
	return (result);
}

void	add_ast(t_ast *front, char type)
{
	t_ast	*buffer;

	buffer = front;
	while (buffer->next != NULL)
		buffer = buffer->next;
	buffer->next = init_ast();
}

// 특정 bit만 뒤집는다. ON -> oFF = 0, OFF -> ON = 1
int	rev_flg(char *flgs, char flg)
{
	if ((*flgs & flg) == flg)
	{
		*flgs &= ~flg;
		return (1);
	}
	else
	{
		*flgs |= flg;
		return (0);
	}
}
