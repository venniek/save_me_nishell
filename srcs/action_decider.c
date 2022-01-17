//
// Created by 연규준 on 2022/01/13.
//

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

//size_t actset_siglequotes(char *flgs)
//{
//	*flgs &= ~FLG_SQ;
//	return (CJI);
//}

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

	if (flg == PIPE || flg == RR || flg == LR || flg == RRR || flg == LRR)
		rev_flg(flgs, FLG_RD);
	if (flg == FLG_DQ || flg == FLG_SQ || flg == FLG_DL)
	{
		result = CJI;
		rev_flg(flgs, flg);
	}
	else if (flg == PIPE)
		result = CJINP;	//4
	else if (flg == RR)
		result = CJINR;	//5
	else if (flg == LR)
		result = CJINL;	//6
	else if (flg == RRR)
		result = CJJINR;	//10
	else if (flg == LRR)
		result = CJJINL;	//11
	else if (flg == EXCL)
		result = HJI;	//18
	else if (flg == WHITE)
		result = CJIAW;		//14
	else
		result = CJI;	//1
	return (result);
}

// 입력된 문자열을 확인해서 확인해봐야하는 문자를 보내는 함수.
size_t	get_actindex(const char *str, const char state)
{
	if (*str == '\0')
		return (decide_actset(FIN));
	else if (*str == '~' && state == 's')
		return decide_actset(EXCL);
	else if (*str == '\'')
		return decide_actset(FLG_SQ);
	else if (*str == '"')
		return decide_actset(FLG_DQ);
	else if (*str == '$')
		return decide_actset(FLG_DL);
	else if (ft_isWhite(*str))
		return decide_actset(WHITE);
	else if (*str == '|')
		return decide_actset(PIPE);
	else if ((*str == '>') && *(str + 1) == '>')
		return decide_actset(RRR);
	else if (*str == '>')
		return decide_actset(RR);
	else if ((*str == '<') && *(str + 1) == '<')
		return decide_actset(LRR);
	else if (*str == '<')
		return decide_actset(LR);
	return (J);
}

size_t	actset_redirection()

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
		{
			flgs &= ~FLG_SQ;
			result = CJI;
		}
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