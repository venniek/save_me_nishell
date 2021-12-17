#include "../header/minishell.h"
#include <string.h>

#define	FLG_ON 1
#define	FLG_OFF 0
#define FLG_NQ	0b0000	// No Quotes FLG ON
#define MSK_NQ	0b0011	// Mask for checking single/double quotes
#define	FLG_SQ	0b0001	// Single Quotes / Single Quotes FLG ON
#define	FLG_DQ	0b0010	// Double Quotes / Double Quotes FLG ON
#define FLG_BS	0b0100	// Backslash / Backslash FLG ON
#define FLG_DL	0b1000	// Dolloar sign / Dolloar sign FLG ON
#define MSK_DL	0b1000

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

// 밑에 구분은 gnl처럼 더 읽을게 없을때까지 NULL을 반환하는...?
// 아니다 차라리 반환에만 쓰이는 struct를 만들어서
// 상태정보 + 변환된 문자열을 계속출력하게
/* Case1. qutos가 아무것도 ON 되지 않았을 때
*		qutos가 아닐때	: slide를 하나 올리고 다음 글자로.
*			이때, |, ;가 오면 끊어줘야한다...
* 		signle quote일때	: flg[0]을 ON으로 만들고 다음 글자.
* 		double quote일때	: flg[1]을 ON으로 만들고 다음 글자.
* 			이때, $, \가 오면 이를 치환해주여야한다. -> 일단
* Case2. signle quote가 ON 되었을 때
* 		qutos가 아닐때	: slide를 하나 올리고 다음 글자로, 이때 모든 특수문자는 무시.
* 		signle quote일때 : flg[0]을 OFF으로 만들고 다음 글자.
* 		double quote일때	: 일반문자로 인식하여 다음문자.
* Case3. double quote가 ON 되었을 때
* 		qutos가 아닐때	: slide를 하나 올리고 다음 글자로
* 		signle quote일때	: 일반문자로 인식하여 다음문자.
* 		double quote일때 : flg[1]을 OFF으로 만들고 다음 글자.
*/
/*
 * strlcat을 사용하는 방법
 * ', "플래그가 없으면 space,',"가 나올때까지 길이를 잰 다음에 "\0"만 있는 문자열에 strlcat(빈문자열, 시작위치, 길이)을 한다.
 * '플래그가 있으면 '만날때까지 길이를 재고 strlcat하되, \를 만나고 특정 조건을 만족하면 \전까지 끊어서 strlcat한 다음,
 */

void	set_flg() {

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

char	**add_nstring(char **old, char *line, int n) {
	char	**result;
	char 	*new_line;

	new_line = ft_strndup(line, n);
	result = ft_addonestring(old, new_line);
	free(new_line);
	return(result);
}

int 	get_type(char *str) {
	if (*str == '>') {
		if (*(++str) == '>')
			return (TYPE_RRREDIR);
		else if (*(++str) == '<')
			return (TYPE_ERROR);
		else
			return (TYPE_RREDIR);
	}
	else if (*str == '<') {
		if (*(++str) == '>')
			return (TYPE_ERROR);
		else if (*(++str) == '<')
			return (TYPE_LRREDIR);
		else
			return (TYPE_LREDIR);
	}
	else
		return (TYPE_CMDS);
}

// 입력된 문자를 바탕으로, 플래그를 세팅하는 함수.
// flg의 변화가 생기면, 그전까지 입력된 것을 전부 문자열로 보낸다.(플래그가 ON되게 한 문자는 제외.)
int		set_flgs(char c, char *flgs) {
	// c가 '인경우
	if (c == '\'') {
		if ((*flgs & MSK_NQ) == FLG_NQ)
			*flgs = *flgs | FLG_SQ;
		else if ((*flgs & MSK_NQ) == FLG_SQ)
			*flgs = *flgs & !FLG_SQ;
		else
			return 0;	
	}
	else if (c == '\"') {
		if ((*flgs & MSK_NQ) == FLG_NQ)
			*flgs = *flgs | FLG_DQ;
		else if ((*flgs & MSK_NQ) == FLG_DQ)
			*flgs = *flgs & !FLG_DQ;
		else
			return 0;
	}
	/* $는 '가 아닌 상태에서만 유효하다.
	 * $가 끝나는 조건은 화이트스페이스, "가 끝나거나 시작, '시작되는 시점
	 * 
	 * 
	*/
	/*
	else if (c == '$') {
		
		if ((*flgs & MSK_DL) == FLG_DL)
			*flgs = *flgs | FLG_DL;
		else if ((*flgs & MSK_DL) == FLG_DL)
			*flgs = *flgs & !FLG_DL;
	}
	else if (ft_isWhite(c) == true && )
	*/
	else
		return 0;
	return 1;
}

// flgs[0] : '', flg[1] : ""
// flg[3] : \, flg[4] : $
t_ast	*paser(char *line) {
	char 	flgs;
	t_ast 	*result;
	t_ast	*ptr_result;
	int		idx;
	int 	slide;

	idx = 0;
	slide = 0;
	flgs = 0;
	result = init_ast();
	ptr_result = result;
	while (line[idx + slide]) {
		while (ft_isWhite(line[idx]))
			++idx;
		// 리다리렉션 ->
		result->type = get_type(line[idx]);
		if (result->type == TYPE_ERROR)
			return (NULL);	// 별도 처리 방법 만들어야 할듯
		else if (result->type != TYPE_CMDS)
			idx++;
		while (1)
		{
			// ", '에 따라서 flg를 끄고 켠다. -> 함수로?
			if (set_flgs(line[idx + slide], &fls)) {
				// add_nstring(ptr_result->text, &line[idx], slide);
				sstrncat(ptr_result->text, &line[idx], slide);
				// cat해주어야 할듯
				++slide;
				break ;
			}
			if (((flgs & MSK_NQ) == FLG_NQ && line[idx + slide] == ' ') || line[idx + slide] == '\0') {
				add_nstring(ptr_result->text, &line[idx], slide);
				++slide;
				break ;
			}
			// 파이프 -> |가 있기만 하면 됨. 띄어쓰니는 상관 없음.
	 		if ((flgs& MSK_NQ) == FLG_NQ && line[idx + slide] == '|') {
				if (slide != 0)
					add_nstring(ptr_result->text, &line[idx], slide);
				ptr_result->next = init_ast();
				ptr_result = ptr_result->next;
				++slide;
				break ;
			}
			++slide;
		}
		idx += slide;
		slide = 0;
	}
	return (result);
}

