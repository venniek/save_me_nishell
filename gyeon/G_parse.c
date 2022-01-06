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
#define JUMP 'J'
#define ALNUM 'A'
#define FIN 'F'

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
	if (flg == FIN) {
		// if ((flgs & (FLG_SQ | FLG_DQ)) == (FLG_SQ | FLG_DQ))
		if ((flgs & FLG_DL) == FLG_DL)
			result = ENV;
		else
			result = CAT;
		flgs = 0;
	}
	else if ((flgs & FLG_SQ) == FLG_SQ) {
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
			else if (flg == FLG_DL)
				;
			else
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

	result = (t_ast *) excep_malloc(sizeof(t_ast));
	result->type = TYPE_CMDS;
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
	front->next->type = type;
	// front->next->text = ft_addonestring(front->next->text, "");
	return (front->next);
}

// 입력된 문자열을 확인해서 확인해봐야하는 문자를 보내는 함수.
char	get_action(char *str) {
	// '플래그 상태
	if (*str == '\0')
		return (FIN);
	else if (*str == '\'')
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
	size_t len_src;

	if (leng == 0)
		return NULL;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (len_dst > leng)
		return NULL;
	result = (char *) excep_malloc(leng);
	result[0] = '\0';
	ft_strlcat(result, dst, len_dst + 1);
	ft_strlcat(result, src, leng);
	return (result);
}

// flgs[0] : '', flg[1] : ""
// flg[3] : \, flg[4] : $
t_ast	*paser(char *line, char **env) {
	t_ast 	*result;
	t_ast	*ptr_result;
	int		idx;
	int 	slide;
	char 	act;
	char	*cursor;
	char	*temp_cursor;
	char	*env_value;

	idx = 0;
	slide = 0;
	result = init_ast();
	ptr_result = result;
	//ptr_result->text = ft_addonestring(ptr_result->text, "");
	//cursor = (ptr_result->text)[ft_sstrlen(ptr_result->text) - 1];
	cursor = (char *) excep_malloc(1);
	cursor[0] = '\0';
	while (1) {
		act = get_action(&line[idx + slide]);
		if (act == CAT) {
			if (slide != 0) {
				// ft_strlcat(cursor, &line[idx], slide + ft_strlen(cursor) + 1);
				temp_cursor = malloc_n_lcat(cursor, &line[idx], slide + ft_strlen(cursor) + 1);
				free(cursor);

				cursor = temp_cursor;
			}
			idx += slide + 1;
			slide = 0;
		} else if (act == JUMP)
			++slide;
		else if (act == PIPE || act == RR || act == RRR || act == LR || act == LRR) {
			if (slide != 0) {
				// ft_strlcat(cursor, &line[idx], slide + ft_strlen(cursor) + 1);
				temp_cursor = malloc_n_lcat(cursor, &line[idx], slide + ft_strlen(cursor) + 1);
				free(cursor);
				cursor = temp_cursor;
				ptr_result->text = ft_addonestring(ptr_result->text, cursor);
			}
			ptr_result = add_ast(result, PIPE);
//			ptr_result->text = ft_addonestring(ptr_result->text, "");
//			cursor = (ptr_result->text)[ft_sstrlen(ptr_result->text) - 1];
			cursor = (char *) excep_malloc(1);
			cursor[0] = '\0';
			idx += slide + 1;
			if (act == RR || act == RRR || act == LR || act == LRR)
				++idx;
			slide = 0;
		} else if (act == WHITE) {
			if (slide != 0) {
				// ft_strlcat(cursor, &line[idx], slide + ft_strlen(cursor) + 1);
				temp_cursor = malloc_n_lcat(cursor, &line[idx], slide + ft_strlen(cursor) + 1);
				free(cursor);
				cursor = temp_cursor;
				ptr_result->text = ft_addonestring(ptr_result->text, cursor);
				cursor = (char *) excep_malloc(1);
				cursor[0] = '\0';
			}
			idx += slide + 1;
			slide = 0;
			while (1) {
				if (line[idx + slide] == '\0' || !ft_isWhite(line[idx + slide]))
					break;
				++idx;
			}
//			ptr_result->text = ft_addonestring(ptr_result->text, "");
//			cursor = (ptr_result->text)[ft_sstrlen(ptr_result->text) - 1];
		} else if (act == ENV) {
			if (slide != 0) {
				env_value = lookup_value(&line[idx], slide, env);
				if (env_value != NULL) {
					// ft_strlcat(cursor, env_value, ft_strlen(cursor) + ft_strlen(env_value) + 1);
					temp_cursor = malloc_n_lcat(cursor, env_value, ft_strlen(cursor) + ft_strlen(env_value) + 1);
					free(cursor);
					cursor = temp_cursor;
					free(env_value);
				}
			}
			idx += slide + 1;
			slide = 0;

		}
		else if (act == FIN) {
			if (set_flg(FIN) == ENV && slide != 0) {
				env_value = lookup_value(&line[idx], slide, env);
				if (env_value != NULL) {
					// ft_strlcat(cursor, env_value, ft_strlen(cursor) + ft_strlen(env_value) + 1);
					temp_cursor = malloc_n_lcat(cursor, env_value, ft_strlen(cursor) + ft_strlen(env_value) + 1);
					free(cursor);
					cursor = temp_cursor;
					free(env_value);
				}
			}
			else if (slide != 0){
				temp_cursor = malloc_n_lcat(cursor, &line[idx], slide + ft_strlen(cursor) + 1);
				free(cursor);
				cursor = temp_cursor;
			}
			if (cursor[0] != '\0')
				ptr_result->text = ft_addonestring(ptr_result->text, cursor);
			free(cursor);
			break ;
		}
	}
	return (result);
}

