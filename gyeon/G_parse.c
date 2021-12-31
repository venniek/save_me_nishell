#include "../header/minishell.h"
#include <string.h>

#define TRUE 1
#define FALSE 0
#define FLG_SQ 0b00000001
#define FLG_DQ 0b00000010
#define FLG_DL 0b00000100

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

// 2 : $
int set_flg(char flg) {
	static char flgs = 0b00000000;

	if (flg == FLG_SQ) {
		if ((flgs | flg) == flg) {
			flgs = 0;
			return 1;
		}
		else
			flgs = flg;
	}
	else if (flg == FLG_DQ) {
		if ((flgs | flg) == flg) {
			if ((flgs | FLG_DL) == FLG_DL))
				return 2;
			flgs = 0;
			return 1;
		}
		else
			flgs = flg;
	}
	return 0;
}

void unset_flg(char *flgs, char flg) {
	*flgs |= ~flg;
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

char	get_action(char *str) {
	// '플래그 상태
	if (*str == '\'') {
		return set_flg();
	}
	// " 플래그 상태
	else if (flgs) {
		if (*str == '\'')
			*flgs = 0;
	}
	// $플래그 상태
	else if (flgs) {

	}
	else {
		;
	}
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

	while (line[idx + slide] != '\0') {

	}
	return (result);
}

