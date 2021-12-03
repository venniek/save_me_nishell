/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 22:03:39 by gyeon             #+#    #+#             */
/*   Updated: 2021/08/20 14:12:23 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_st;

	new_st = NULL;
	if (lst != NULL && f != NULL)
	{
		new = ft_lstnew(f(lst->content));
		new_st = new;
		lst = lst->next;
		while (lst != NULL && new != NULL)
		{
			new->next = ft_lstnew(f(lst->content));
			if (new->next == NULL)
			{
				ft_lstclear(&new_st, del);
				new_st = NULL;
				break ;
			}
			new = new->next;
			lst = lst->next;
		}
	}
	return (new_st);
}
