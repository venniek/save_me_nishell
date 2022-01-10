#include "../header/minishell.h"
#include <errno.h>

void b_cd(char **cmd)
{
	// 인자가 없으면 home으로 간다. 함수 들어오기 전에 처리
	// 인자 여러개면 그냥 무시! 첫번째 인자로 이동
	if (!cmd)
		return ;
	// 에러 종류 따라 출력문 다르게
	if (chdir(cmd[1]))
		printf("minishell: cd: %s: %s\n", cmd[1], strerror(errno));
}
