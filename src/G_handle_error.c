#include "../header/minishell.h"

void err_malloc() {
	write(2, "fatal : malloc false.\n", 22);
	exit(1);
}