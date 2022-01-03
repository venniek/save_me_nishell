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
#define CAT 'C'
#define ENV 'E'
#define JUMP 'J'
#define ALNUM 'A'

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
// 0 : 무시, 1 : cat, 2 : 환경변수cat
char set_flg(char flg) {
	static	char flgs = 0;
	char		result;

	result = JUMP;
	// SQ flg
	if ((flgs & FLG_SQ) == FLG_SQ) {
		// SQ빼고 전부 무시
		if (flg == FLG_SQ) {
			// cat 신호
			result = CAT;
			flgs &= ~FLG_SQ;
		}
	}
	else if ((flgs & FLG_DL) == FLG_DL) {
		// 알파벳, 숫자 이외에게 오면(공백, 특수, 한글) $를 끝낸다.
		if (flg != ALNUM) {
			result = ENV;
			if ((flgs & FLG_DQ) == FLG_DQ && flg == FLG_DQ)
				rev_flg(&flgs, flg);
			rev_flg(&flgs, FLG_DL);
		}
	}
	//
	else if ((flgs & FLG_DQ) == FLG_DQ) {
		// DL, DQ 유효. 이때 뭐가 오던간에 플래그를 반전시키고, 이전까지의 들을 cat한다.
		if (flg == FLG_DQ || flg == FLG_DL) {
			result = CAT;
			rev_flg(&flgs, flg);
			// DL를 cat하고
		}
	}
	else {
		if (flg == FLG_DQ || flg == FLG_SQ || flg == FLG_DL) {
			result = CAT;
			rev_flg(&flgs, flg);
		}
		else
			result = flg;
	}
	return result;
}

// 새 ast를 init하고, 그것을 반환
t_ast	*init_ast() {
	t_ast* result;

	result = excep_malloc(sizeof(t_ast));
	result->type = TYPE_UNDEFINED;
	result->text = (char **) excep_malloc(sizeof(char *) * 1);
	result->text[0] = NULL;
	return (result);
}

// 입력된 문자열을 확인해서 확인해봐야하는 문자를 보내는 함수.
char	get_action(char *str) {
	// '플래그 상태
	if (*str == '\'')
		return set_flg(FLG_SQ);
	// " 플래그 상태
	else if (*str == '"')
		return set_flg(FLG_DQ);
	// $플래그 상태
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
	return (JUMP);
}

// flgs[0] : '', flg[1] : ""
// flg[3] : \, flg[4] : $
t_ast	*paser(char *line) {
	t_ast 	*result;
	t_ast	*ptr_result;
	int		idx;
	int 	slide;
	char 	act;

	idx = 0;
	slide = 0;
	result = init_ast();
	ptr_result = result;

	while (line[idx + slide] != '\0') {
		act = get_action(&line[idx + slide]);
		if (act == CAT) {
			idx += slide + 1;
			slide = 0;
		}
		else if (act == JUMP)
			++slide;
		else if (act == PIPE) {
			idx += slide + 1;
			slide = 0;
		}
		else if (act == RR || act == RRR || act == LR || act == LRR) {
			idx += slide + 1;
			slide = 0;
		}
		else if (act == WHITE) {
			idx += slide + 1;
			slide = 0;
			while (1) {
				if (line[idx + slide] == '\0' || !ft_isWhite(line[idx + slide]))
					break;
				++idx;
			}
		}
		else if (act == ENV) {
			idx += slide + 1;
			slide = 0;
		}
	}
	return (result);
}

