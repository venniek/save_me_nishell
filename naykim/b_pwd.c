#include "../header/minishell.h"

void b_pwd()
{
	// 뒤에 적힌 인자들 전부 무시. 함수 들어오기 전에 처리
	char *buf;

	buf = getcwd(0, 100);
	printf("%s\n", buf);
	free(buf);
}
