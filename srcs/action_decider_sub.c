/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_decider_sub.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 21:23:40 by gyeon             #+#    #+#             */
/*   Updated: 2022/01/25 18:16:50 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

size_t	dollar_dollarquestion(const char *str)
{
	if (*(str + 1) == '?')
		return (decide_actset(DLQUESTION));
	return (decide_actset(FLG_DL));
}

size_t	if_flg_singlequote(char *flgs)
{
	(*flgs) &= ~FLG_SQ;
	return (CJI);
}
