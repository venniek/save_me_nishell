//
// Created by 연규준 on 2022/01/13.
//

#include "../header/minishell.h"

size_t	actset_fin(char *flgs)
{
	size_t	result;

	if ((*flgs & FLG_DL) == FLG_DL)
		result = EAF;
	else
		result = CAF;
	*flgs = 0;
	return (result);
}

size_t actset_siglequotes(char *flgs)
{
	*flgs &= ~FLG_SQ;
	return (CJI);
}

size_t actset_dollar(char *flgs, char flg)
{
	size_t result;

	result = J;
	if (flg != ALNUM)
	{
		if ((*flgs & FLG_DQ) == FLG_DQ && flg != FLG_DQ)
			result = EIJ;
		else if (flg == PIPE)
			result = EJINP;
		else if (flg == RR)
			result = EJINR;
		else if (flg == LR)
			result = EJINL;
		else if (flg == RRR)
			result = EJJINR;
		else if (flg == LRR )
			result = EJJINL;
		else if (flg == WHITE)
			result = EJIAW;
		else
			result = EJI;
		if (((*flgs & FLG_DQ) != FLG_DQ && flg == FLG_SQ) || flg == FLG_DQ)
			rev_flg(flgs, flg);
		if (flg != FLG_DL)
			rev_flg(flgs, FLG_DL);
	}
	return (result);
}

size_t	actset_noflgs(char *flgs, char flg)
{
	size_t	result;

	if (flg == FLG_DQ || flg == FLG_SQ || flg == FLG_DL)
	{
		result = CJI;
		rev_flg(flgs, flg);
	}
	else if (flg == PIPE)
		result = CJINP;
	else if (flg == RR)
		result = CJINR;
	else if (flg == LR)
		result = CJINL;
	else if (flg == RRR)
		result = CJJINR;
	else if (flg == LRR )
		result = CJJINL;
	else if (flg == EXCL)
		result = HJI;
	else if (flg == WHITE)
		result = CJIAW;
	else
		result = CJI;
	return (result);
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
	size_t		result;

	result = J;
	if (flg == FIN)
		result = actset_fin(&flgs);
	else if ((flgs & FLG_SQ) == FLG_SQ)
	{
		if (flg == FLG_SQ)
			result = actset_siglequotes(&flgs);
	}
	else if ((flgs & FLG_DL) == FLG_DL)
		result = actset_dollar(&flgs, flg);
	else if ((flgs & FLG_DQ) == FLG_DQ)
	{
		if (flg == FLG_DQ || flg == FLG_DL)
		{
			result = CJI;
			rev_flg(&flgs, flg);
		}
	}
	else
		result = actset_noflgs(&flgs, flg);
	return result;
}