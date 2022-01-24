/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_decider_sub.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 21:23:40 by gyeon             #+#    #+#             */
/*   Updated: 2022/01/24 13:43:56 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

size_t	doller_dollerquestion(const char *str)
{
	if (*(str + 1) == '?')
		return (decide_actset(DLQUESTION));
	return (decide_actset(FLG_DL));
}

size_t	if_flg_singlequete(char *flgs)
{
	(*flgs) &= ~FLG_SQ;
	return (CJI);
}
