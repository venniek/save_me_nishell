/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 18:22:06 by gyeon             #+#    #+#             */
/*   Updated: 2021/08/20 14:11:36 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*pt;

	pt = (t_list *)malloc(sizeof(t_list));
	if (pt != NULL)
	{
		pt->content = content;
		pt->next = NULL;
	}
	return (pt);
}
