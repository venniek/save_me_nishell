#include "../header/minishell.h"
#include <string.h>

#define	FLG_ON 1
#define	FLG_OFF 0
#define FLG_NQ -2	// No Quotes FLG ON
#define FLG_AQ -1	// ALL Quotes FLG ON
#define	FLG_SQ 0	// Single Quotes / Single Quotes FLG ON
#define	FLG_DQ 1	// Double Quotes / Double Quotes FLG ON
#define FLG_BS 2	// Backslash / Backslash FLG ON
#define FLG_DL 3	// Dolloar sign / Dolloar sign FLG ON

t_ast	*paser(char *line) {
	// flgs[0] : '', flg[1] : ""
	// flg[3] : \, flg[4] : $
	char 	flgs[2];
	t_ast 	*result;
	t_ast	*ptr_result;
	int		idx;
	int 	slide;

	idx = 0;
	slide = 0;
	flgs[0] = 0;
	flgs[1] = 0;
	result = excep_malloc(sizeof(t_ast));
	ptr_result = result;
	// 밑에 구분은 gnl처럼 더 읽을게 없을때까지 NULL을 반환하는...?
	// 아니다 차라리 반환에만 쓰이는 struct를 만들어서
	// 상태정보 + 변환된 문자열을 계속출력하게
	while (line[idx] != '\0') {
		while (line[idx] != '\0') {
			if (line[idx++] != ' ')
				break ;
		}
		while (line[idx + slide]) {
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
			if (flgs[FLG_SQ] == FLG_ON) {
				while (line[idx + slide] == '\'') {
					if (line[idx + slide] == '\\') {
						if (flgs[FLG_BS] == FLG_ON)
							; // \\를 그대로 출력하게...
						else
							flgs[FLG_BS] = FLG_ON;
					}
					++slide;
				}
			}
			else if (flgs[FLG_DQ] == FLG_ON) {
				while (line[idx + slide++] == '\"');
				// 특수문자를 변환하는
			}
			if (line[idx + slide] == ' ')

			++slide;
		}
	}

	return (result);
}


t_list	*parser_sep(char *line, char sep) {
	int		i;
	t_list	*result;
	char	**string_set;

	i = 0;
	string_set = ft_split(line, sep);
	result = ft_lstnew(ft_strtrim(string_set[i++], " "));
	while (string_set[i] != NULL) {
		ft_lstadd_back(&result, ft_lstnew(ft_strtrim(string_set[i++], " ")   ));
	}
	free(string_set);
	return (result);
}

t_list	*parse_line(char *line) {
	char	**comm_set;
	t_list	*result;
	t_list	*temp_list;
	char	*temp;
	// 일단 ;별로 나누어서 t_list를 만들고,
	result = parser_sep(ft_strtrim(line, " ") , ';');
	// result를 순회하면서 각 content를 |기준의
	temp_list = result;
	while (temp_list != NULL) {
		temp = temp_list->content;
		temp_list->content = parser_sep(ft_strtrim((char *)temp, " "), '|');
//		char *what = ((t_list *)(temp_list->content))->content;
		free(temp);
		temp_list = temp_list->next;
	}
	return (result);
}