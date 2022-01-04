#include "../header/minishell.h"
#include <errno.h>

void b_cd(char *path)
{
	// 인자가 없으면 home으로 간다. 함수 들어오기 전에 처리
	if (!path)
		return ;
	// 에러 종류 따라 출력문 다르게
	if (chdir(path))
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
}
