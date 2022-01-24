/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_decider.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naykim <naykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 21:23:49 by gyeon             #+#    #+#             */
/*   Updated: 2022/01/24 20:32:13 by naykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

size_t	actset_fin(char *flgs)
{
	size_t	result;

	if ((*flgs & FLG_DQ) == FLG_DQ || (*flgs & FLG_SQ) == FLG_SQ)
		result = P_ERR;
	else if ((*flgs & FLG_DL) == FLG_DL)
		result = EAF;
	else
		result = CAF;
	*flgs = 0;
	return (result);
}

size_t	actset_dollar(char *flgs, char flg)
{
	size_t	result;

	result = J;
	if (flg == ALNUM)
		return (result);
	if (((*flgs & FLG_DQ) == FLG_DQ && flg != FLG_DQ) || flg == NOT_ALP_NUM)
		result = EIJ;
	else if (flg >= PIPE && flg <= LRR)
	{
		if (flg == LRR)
			*flgs |= FLG_RD;
		result = EJINP + (flg - PIPE);
	}
	else if (flg == WHITE)
		result = EJIAW;
	else if (flg == DLQUESTION)
		result = EJIEJI;
	else
		result = EJI;
	if (((*flgs & FLG_DQ) != FLG_DQ && flg == FLG_SQ) || flg == FLG_DQ)
		rev_flg(flgs, flg);
	if (flg != FLG_DL)
		*flgs &= ~FLG_DL;
	return (result);
}

size_t	actset_noflgs(char *flgs, char flg)
{
	if (flg == LRR)
		*flgs |= FLG_RD;
	if (flg == FLG_DQ || flg == FLG_SQ || flg == FLG_DL)
	{
		if (!((*flgs & FLG_RD) == FLG_RD && flg == FLG_DL))
		{
			rev_flg(flgs, flg);
			return (CJI);
		}
	}
	else if (flg >= PIPE && flg <= LRR)
	{
		if (flg != LRR)
			*flgs &= ~FLG_RD;
		return (CJINP + (flg - PIPE));
	}
	else if (flg == EXCL)
		return (HJI);
	else if (flg == WHITE)
		return (CJIAW);
	else if (flg == DLQUESTION)
		return (CJIEJI);
	else if (flg != NOT_ALP_NUM)
		return (CJI);
	return (J);
}

size_t	get_actindex(const char *str, const char state)
{
	if (*str == '\0')
		return (decide_actset(FIN));
	else if (*str == '~' && state == 's')
		return (decide_actset(EXCL));
	else if (*str == '\'')
		return (decide_actset(FLG_SQ));
	else if (*str == '"')
		return (decide_actset(FLG_DQ));
	else if (*str == '$')
		return (dollar_dollarquestion(str));
	else if (ft_isWhite(*str))
		return (decide_actset(WHITE));
	else if (*str == '|')
		return (decide_actset(PIPE));
	else if ((*str == '>') && *(str + 1) == '>')
		return (decide_actset(RRR));
	else if (*str == '>')
		return (decide_actset(RR));
	else if ((*str == '<') && *(str + 1) == '<')
		return (decide_actset(LRR));
	else if (*str == '<')
		return (decide_actset(LR));
	else if (ft_isalnum(*str) == 0)
		return (decide_actset(NOT_ALP_NUM));
	return (J);
}

// 확인해봐야하는 동작을 받아서 어떤 동작을할지 제어하는 함수.
/*
 * C(cat)			: idx부터 직전까지의 문자를 버퍼에 cat한다.
 * E(Env)			: idx부터 직전짜기의 문자를 환경변수에서 검색하여 cat한다.
 * J(Jump)			: ++slide
 * A(Addnewline)	: text에 한줄 추가하고 버퍼를 변경한다.
 * N(Newlist)		: 새로운 list를 추가하고, 버퍼 및 리스트 커서를 옮긴다.
 */
size_t	decide_actset(char flg)
{
	static char	flgs = 0;

	if (flg == FIN)
		return (actset_fin(&flgs));
	else if ((flgs & FLG_SQ) == FLG_SQ)
	{
		if (flg == FLG_SQ)
			return (if_flg_singlequete(&flgs));
	}
	else if ((flgs & FLG_DL) == FLG_DL && (flgs & FLG_RD) != FLG_RD)
		return (actset_dollar(&flgs, flg));
	else if ((flgs & FLG_DQ) == FLG_DQ)
	{
		if (flg == DLQUESTION)
			return (CJIEJI);
		if (flg == FLG_DQ || (flg == FLG_DL && (flgs & FLG_RD) != FLG_RD))
		{
			rev_flg(&flgs, flg);
			return (CJI);
		}
	}
	else
		return (actset_noflgs(&flgs, flg));
	return (J);
}
