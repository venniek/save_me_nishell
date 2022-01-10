#include "../header/minishell.h"
#include <string.h>

#define TRUE 1
#define FALSE 0

#define FLG_RESET 0
#define FLG_SQ 0b00000001
#define FLG_DQ 0b00000010
#define FLG_DL 0b00000100
#define WHITE 'W'
#define PIPE 'P'
#define RR 'r'
#define RRR 'R'
#define LR 'l'
#define LRR 'L'
#define CAT 'C'
#define ENV 'E'
#define ENV2 'e'
#define JUMP 'J'
#define ALNUM 'A'
#define FIN 'F'

#define J 		0
#define CJI		1
#define EJI		2
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

#define TYPE_UNDEFINED	0
#define TYPE_CMDS		1
#define TYPE_LREDIR		2
#define TYPE_RREDIR		3
#define TYPE_LRREDIR	4
#define TYPE_RRREDIR	5
#define TYPE_ERROR		-1

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


// 확인해봐야하는 동작을 받아서 어떤 동작을할지 제어하는 함수.
/*
 * C(cat)			: idx부터 직전까지의 문자를 버퍼에 cat한다.
 * E(Env)			: idx부터 직전짜기의 문자를 환경변수에서 검색하여 cat한다.
 * J(Jump)			: ++slide
 * A(Addnewline)	: text에 한줄 추가하고 버퍼를 변경한다.
 * N(Newlist)		: 새로운 list를 추가하고, 버퍼 및 리스트 커서를 옮긴다.
 */
size_t	set_flg(char flg)
{
	static char	flgs = 0;
	char		result;

	result = J;
	if (flg == FIN)
	{
		if ((flgs & FLG_DL) == FLG_DL)
			result = EAF;
		else
			result = CAF;
		flgs = 0;
	}
	else if ((flgs & FLG_SQ) == FLG_SQ)
	{
		if (flg == FLG_SQ)
		{
			result = CJI;
			flgs &= ~FLG_SQ;
		}
	}
	else if ((flgs & FLG_DL) == FLG_DL)
	{
		if (flg != ALNUM)
		{
			if ((flgs & FLG_DQ) == FLG_DQ && flg != FLG_DQ)
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
			else
				result = EJI;
			if (((flgs & FLG_DQ) != FLG_DQ && flg == FLG_SQ) || flg == FLG_DQ)
				rev_flg(&flgs, flg);
			if (flg != FLG_DL)
				rev_flg(&flgs, FLG_DL);
		}
	}
	else if ((flgs & FLG_DQ) == FLG_DQ)
	{
		if (flg == FLG_DQ || flg == FLG_DL)
		{
			result = CJI;
			rev_flg(&flgs, flg);
		}
	}
	else {
		if (flg == FLG_DQ || flg == FLG_SQ || flg == FLG_DL)
		{
			result = CJI;
			rev_flg(&flgs, flg);
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
		else
			result = CJI;
		if (flg == WHITE)
			result = CJIAW;
	}
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

t_ast	*add_ast(t_ast *front, char type) {
	while (front->next != NULL) {
		front = front->next;
	}
	front->next = init_ast();
	if (type == PIPE)
		front->next->type = 'c';
	else
		front->next->type = type;
	return (front->next);
}

// 입력된 문자열을 확인해서 확인해봐야하는 문자를 보내는 함수.
size_t	get_action(const char *str) {
	if (*str == '\0')
		return (set_flg(FIN));
	else if (*str == '\'')
		return set_flg(FLG_SQ);
	else if (*str == '"')
		return set_flg(FLG_DQ);
	else if (*str == '$')
		return set_flg(FLG_DL);
	else if (ft_isWhite(*str))
		return set_flg(WHITE);
	else if (*str == '|')
		return set_flg(PIPE);
	else if (*str == '>') {
		if (*(str + 1) == '>')
			return set_flg(RRR);
		else
			return set_flg(RR);
	}
	else if (*str == '<') {
		if (*(str + 1) == '<')
			return set_flg(LRR);
		else
			return set_flg(LR);
	}
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

char	**make_actset()
{
	char	**result;

	result = (char **) excep_malloc(sizeof(char *) * 19);
	result[J] = ft_strdup("J");
	result[CJI] = ft_strdup("CJI");
	result[EJI] = ft_strdup("EJI");
	result[EIJ] = ft_strdup("EIJ");
	result[CJINP] = ft_strdup("CJIAP");
	result[CJINR] = ft_strdup("CJIAR");
	result[CJINL] = ft_strdup("CJIAL");
	result[EJINP] = ft_strdup("EJIAP");
	result[EJINR] = ft_strdup("EJIAR");
	result[EJINL] = ft_strdup("EJIAL");
	result[CJJINR] = ft_strdup("CJJIAr");
	result[CJJINL] = ft_strdup("CJJIAl");
	result[EJJINR] = ft_strdup("EJJIAr");
	result[EJJINL] = ft_strdup("EJJIAl");
	result[CJIAW] = ft_strdup("CJIAW");
	result[EJIAW] = ft_strdup("EJIAW");
	result[CAF] = ft_strdup("CAF");
	result[EAF] = ft_strdup("EAF");
	result[18] = NULL;
	return (result);
}

t_ast	*parser(char *line, char **env) {
	t_ast 	*result;
	t_ast	*ptr_result;
	size_t	idx;
	size_t 	slide;
	size_t	idx_act;
	char 	*act;
	char	*cursor;
	char	*temp_cursor;
	char	*env_value;
	char	**actset;
	char	f;

	idx = 0;
	slide = 0;
	idx_act = 0;
	f = 0;
	result = init_ast();
	ptr_result = result;
	cursor = (char *) excep_malloc(1);
	cursor[0] = '\0';
	actset = make_actset();
	while (f != 'F') {
		act = actset[get_action(&line[idx + slide])];
		idx_act = 0;
		while (act[idx_act] != '\0')
		{
			if (act[idx_act] == 'J')
				++slide;
			else if (act[idx_act] == 'I')
			{
				idx += slide;
				slide = 0;
			}
			else if (act[idx_act] == 'C')
			{
				temp_cursor = malloc_n_lcat(cursor, &line[idx], slide + ft_strlen(cursor) + 1);
				free(cursor);
				cursor = temp_cursor;
			}
			else if (act[idx_act] == 'E')
			{
				env_value = lookup_value(&line[idx], slide, env);
				if (env_value != NULL)
				{
					temp_cursor = malloc_n_lcat(cursor, env_value, ft_strlen(cursor) + ft_strlen(env_value) + 1);
					free(cursor);
					cursor = temp_cursor;
					free(env_value);
				}
			}
			else if (act[idx_act] == 'A')
			{
				if (cursor[0] != '\0')
				{
					ptr_result->text = ft_addonestring(ptr_result->text, cursor);
					cursor = (char *) excep_malloc(1);
					cursor[0] = '\0';
				}
			}
			else if (act[idx_act] == 'W')
			{
				idx += slide;
				slide = 0;
				while (1) {
					if (line[idx + slide] == '\0' || !ft_isWhite(line[idx + slide]))
						break;
					++idx;
				}
			}
			else if (act[idx_act] == 'P' || act[idx_act] == 'R' || act[idx_act] == 'r' || act[idx_act] == 'L' || act[idx_act] == 'l')
			{
				ptr_result = add_ast(result, act[idx_act]);
				cursor = (char *) excep_malloc(1);
				cursor[0] = '\0';
			}
			else if (act[idx_act] == 'F')
			{
				f = 'F';
				free(cursor);
				break ;
			}
			++idx_act;
		}
	}
	return (result);
}


