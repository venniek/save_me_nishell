/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 21:29:09 by gyeon             #+#    #+#             */
/*   Updated: 2022/01/26 14:47:22 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	add_ast(t_ast *front)
{
	t_ast	*buffer;

	buffer = front;
	while (buffer->next != NULL)
		buffer = buffer->next;
	buffer->next = init_ast();
}

void	rev_flg(char *flgs, char flg)
{
	if ((*flgs & flg) == flg)
		*flgs &= ~flg;
	else
		*flgs |= flg;
}
