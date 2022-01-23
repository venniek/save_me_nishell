#include "../header/minishell.h"

size_t	doller_dollerquestion(const char *str)
{
	if (*(str + 1) == '?')
		return (decide_actset(DLQUESTION));
	return (decide_actset(FLG_DL));
}

size_t	if_flg_slinglequete(char *flgs)
{
	(*flgs) &= ~FLG_SQ;
	return (CJI);
}