#include "../header/minishell.h"
#include <string.h>

#define TRUE 1
#define FALSE 0

#define FLG_SQ 0b00000001
#define FLG_DQ 0b00000010
#define FLG_DL 0b00000100
#define WHITE 'W'
#define PIPE 'P'
#define RR 'r'
#define RRR 'R'
#define LR 'l'
#define LRR 'L'
#define ALNUM 'A'
#define EXCL '~'
#define FIN 'F'

#define J 		0
#define CJI		1
#define EJI		2
#define HJI		18
#define EIJ		3
#define CJINP	4
#define CJINR	5
#define CJINL	6
#define EJINP	7
#define EJINR	8
#define EJINL	9
#define CJJINR	10
#define CJJINL	11
#define EJJINR	12
#define EJJINL	13
#define CJIAW	14
#define EJIAW	15
#define CAF		16
#define EAF		17

int ft_isWhite(char c) {
	return ((c >= 9 && c <= 13) || c == 32);
}

// 특정 bit만 뒤집는다. ON -> oFF = 0, OFF -> ON = 1
int	rev_flg(char *flgs, char flg) {
	// ON -> OFF
	if ((*flgs & flg) == flg) {
		*flgs &= ~flg;
		return 1;
	}
	else {
		*flgs |= flg;
		return 0;
	}
}

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

size_t actset_siglequotes(char *flgs, char flg)
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
size_t	assort_actset(char flg)
{
	static char	flgs = 0;
	size_t		result;

	result = J;
	if (flg == FIN)
		result = actset_fin(&flgs);
	else if ((flgs & FLG_SQ) == FLG_SQ)
	{
		if (flg == FLG_SQ)
			result = actset_siglequotes(&flgs, flg);
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

// 새 ast를 init하고, 그것을 반환
t_ast	*init_ast() {
	t_ast* result;

	result = (t_ast *) excep_malloc(sizeof(t_ast));
	result->type = 'c';
	result->text = (char **) excep_malloc(sizeof(char *) * 1);
	result->text[0] = NULL;
	// 다음에 해당 주소를 다시 사용할수 있기 때문에, 한상 NULL로 초기화해주는 습관을 가지자...
	result->next = NULL;
	return (result);
}

void add_ast(t_ast *front, char type) {
	t_ast *cursor;

	cursor = front;
	while (cursor->next != NULL) {
		cursor = cursor->next;
	}

	cursor->next = init_ast();
	if (type == PIPE)
		cursor->next->type = 'c';
	else
		cursor->next->type = type;
	//return (cursor->next);
}

// 입력된 문자열을 확인해서 확인해봐야하는 문자를 보내는 함수.
size_t	get_action(const char *str, const char state)
{
	if (*str == '\0')
		return (assort_actset(FIN));
	else if (*str == '~' && state == 's')
		return assort_actset(EXCL);
	else if (*str == '\'')
		return assort_actset(FLG_SQ);
	else if (*str == '"')
		return assort_actset(FLG_DQ);
	else if (*str == '$')
		return assort_actset(FLG_DL);
	else if (ft_isWhite(*str))
		return assort_actset(WHITE);
	else if (*str == '|')
		return assort_actset(PIPE);
	else if ((*str == '>') && *(str + 1) == '>')
		return assort_actset(RRR);
	else if (*str == '>')
		return assort_actset(RR);
	else if ((*str == '<') && *(str + 1) == '<')
		return assort_actset(LRR);
	else if (*str == '<')
		return assort_actset(LR);
	return (J);
}

char *lookup_value(char *start, size_t leng, char **env) {
		size_t 	idx;
		char	*temp;
		char 	*result;

		idx = 0;
		result = NULL;
		temp = ft_strndup(start, leng);
		while (env[idx] != NULL) {
			if (ft_strncmp(env[idx], temp, ft_strlen(temp)) == 0) {
				if (env[idx][ft_strlen(temp)] == '=')
					result = ft_strdup(&env[idx][ft_strlen(temp) + 1]);
			}
			++idx;
		}
		free(temp);
		return (result);
}

char	*malloc_n_lcat(char *dst, char *src, size_t leng) {
	char *result;
	size_t len_dst;

	if (leng == 0)
		return NULL;
	len_dst = ft_strlen(dst);
	if (len_dst > leng)
		return NULL;
	result = (char *) excep_malloc(leng);
	result[0] = '\0';
	ft_strlcat(result, dst, len_dst + 1);
	ft_strlcat(result, src, leng);
	return (result);
}

//char	**make_actset()
//{
//	char	**result;
//
//	result = (char **) excep_malloc(sizeof(char *) * 19);
//	result[J] = ft_strdup("J");
//	result[CJI] = ft_strdup("CJI");
//	result[EJI] = ft_strdup("EJI");
//	result[EIJ] = ft_strdup("EIJ");
//	result[CJINP] = ft_strdup("CJIAP");
//	result[CJINR] = ft_strdup("CJIAR");
//	result[CJINL] = ft_strdup("CJIAL");
//	result[EJINP] = ft_strdup("EJIAP");
//	result[EJINR] = ft_strdup("EJIAR");
//	result[EJINL] = ft_strdup("EJIAL");
//	result[CJJINR] = ft_strdup("CJJIAr");
//	result[CJJINL] = ft_strdup("CJJIAl");
//	result[EJJINR] = ft_strdup("EJJIAr");
//	result[EJJINL] = ft_strdup("EJJIAl");
//	result[CJIAW] = ft_strdup("CJIAW");
//	result[EJIAW] = ft_strdup("EJIAW");
//	result[CAF] = ft_strdup("CAF");
//	result[EAF] = ft_strdup("EAF");
//	result[HJI] = ft_strdup("HJI");
//	result[19] = NULL;
//	return (result);
//}

void	action_idx(char **line, size_t *slide)
{
	*line += *slide;
	*slide = 0;
}

char	*action_cat(char *dst, char *src, size_t slide)
{
	char	*result;

	if (dst == NULL)
		result = ft_strndup(src, slide);
	else
	{
		result = malloc_n_lcat(dst, src, slide + ft_strlen(dst) + 1);
		free(dst);
	}
	return (result);
}

char	*action_env(char *dst, char *src, char **env, size_t slide)
{
	char	*result;
	char	*env_value;

	env_value = lookup_value(src, slide, env);
	if (env_value != NULL)
	{
		result = action_cat(dst, env_value, ft_strlen(env_value));
		free(env_value);
	}
	else
		return (NULL);
	return (result);
}

t_ast	*get_last(t_ast	*start)
{
	while (start->next != NULL)
		start = start->next;
	return start;
}

char	action_addonestring(t_ast *lst, char **cursor)
{
	if ((*cursor)[0] != '\0')
	{
		lst = get_last(lst);
		lst->text = ft_addonestring(lst->text, *cursor);
		free(*cursor);
	}
	*cursor = NULL;
	return ('s');
}

void action_white(char **line, const size_t *slide)
{
	*line += *slide;
	slide = 0;
	while (1) {
		if (**line == '\0' || !ft_isWhite(**line))
			break;
		++(*line);
	}
}

char action_appendlist(t_ast *result, char **cursor, const char *act)
{
	free(*cursor);
	add_ast(result, *act);
	cursor = NULL;
	return 's';
}

char action_fin(char *cursor)
{
	free(cursor);
	return ('F');
}

char	*get_actset(size_t idx)
{
	static char *actset[20] =
			{"J", "CJI", "EJI", "EIJ", "CJIAP",
			 "CJIAR", "CJIAL", "EJIAP", "EJIAR", "EJIAL",
			 "CJJIAr", "CJJIAl", "EJJIAr", "EJJIAl", "CJIAW",
			 "EJIAW", "CAF", "EAF", "HJI", NULL};
	return (actset[idx]);
}

char	c_to_h(char **cursor, const char *act, char **line, char **env, const size_t *slide)
{
	char		state;

	state = 'm';
	if (*act == 'C')
		*cursor = action_cat(*cursor, *line, *slide);
	else if (*act == 'E')
		*cursor = action_env(*cursor, *line, env, *slide);
	else if (*act == 'H')
		*cursor = action_env(*cursor, "HOME", env, 4);
	else if (*act == 'F')
		state = action_fin(*cursor);
	return (state);
}

char	i_to_w(t_ast *result, char **cursor, const char *act, char **line, size_t *slide)
{
	char		state;

	state = 'm';
	if (*act == 'J')
		++(*slide);
	else if (*act == 'I')
		action_idx(line, slide);
	else if (*act == 'W')
		action_white(line, slide);
	else if (*act == 'P' || *act == 'R' ||
			 *act == 'r' || *act == 'L' || *act == 'l')
		state = action_appendlist(result, cursor, act);
	return (state);
}

t_ast	*parser(char *line, char **env)
{
	t_ast 	*result;
	size_t 	slide;
	char 	*act;
	char	*cursor;
	char 	state;

	slide = 0;
	state = 's';
	result = init_ast();
	cursor = NULL;
	while (state != 'F')
	{
		act = get_actset(get_action(&line[slide], state));
		state = 'm';
		while (*act != '\0')
		{
			if (*act == 'A')
				state = action_addonestring(result, &cursor);
			else if (*act <= 'H')
				state = c_to_h(&cursor, act, &line, env, &slide);
			else
				i_to_w(result, &cursor, act, &line, &slide);
			++act;
		}
	}
	return (result);
}


