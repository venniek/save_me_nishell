#include "../header/minishell.h"
#include <string.h>

#define	FLG_ON 1
#define	FLG_OFF 0
#define FLG_NQ	0b0000	// No Quotes FLG ON
#define MSK_NQ	0b1111	// Mask for checking single quotes
#define	FLG_SQ	0b0001	// Single Quotes / Single Quotes FLG ON
#define	FLG_DQ	0b0010	// Double Quotes / Double Quotes FLG ON
#define FLG_BS	0b0100	// Backslash / Backslash FLG ON
#define FLG_DL	0b1000	// Dolloar sign / Dolloar sign FLG ON

#define TYPE_UNDEFINED	0
#define TYPE_CMDS		1

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

// 새 ast를 init하고, 그것을 반환
t_ast	*init_ast() {
	t_ast* result;

	result = excep_malloc(sizeof(t_ast));
	result->type = TYPE_UNDEFINED;
	result->text = (char **) excep_malloc(sizeof(char *) * 1);
	result->text[0] = NULL;
	return (result);
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
		if (line[idx] != '<' && line[idx] != '>')
			ptr_result->type = TYPE_CMDS;
		while (1) {
			if (((flgs & MSK_NQ) == FLG_NQ && line[idx + slide] == ' ') || line[idx + slide] == '\0') {
				char *temp = ft_strndup(&line[idx], slide);
				ptr_result->text = ft_addonestring(ptr_result->text, temp);
				free(temp);
				++slide;
				break ;
			}
			if ((flgs & MSK_NQ) == FLG_NQ && line[idx + slide] == '|') {
				if (slide != 0) {
					char *temp = ft_strndup(&line[idx], slide);
					ptr_result->text = ft_addonestring(ptr_result->text, temp);
					free(temp);
				}
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

