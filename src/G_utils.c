#include "../header/minishell.h"

void *excep_malloc(int leng) {
	void	*result;

	result = malloc(leng);
	if (result == NULL) 
		err_malloc();
	return (result);
}

void *excep_calloc(size_t count, size_t size) {
	void	*result;

	result = ft_calloc(count, size);
	if (result == NULL)
		err_malloc();
	return (result);
}

size_t ft_sstrlen(char **strstr) {
	size_t leng;

	leng = 0;
	while (strstr[leng] != NULL)
		++leng;
	return (leng);
}

void ft_print_charchar(char **strstr) {   // 지울거예요! 테스트용
	for (int i = 0; i < ft_sstrlen(strstr); i++)
		printf("%s\n", strstr[i]);
}