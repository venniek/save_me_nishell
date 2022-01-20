/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:25:11 by naykim            #+#    #+#             */
/*   Updated: 2022/01/20 17:38:25 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_astlen(t_ast *ast)
{
	int	len;

	len = 0;
	while (ast)
	{
		ast = ast->next;
		len++;
	}
	return (len);
}

t_ast	*ft_astindex(t_ast *ast, int idx)
{
	t_ast	*ret;

	ret = ast;
	while (idx-- > 0)
		ret = ret->next;
	return (ret);
}

void	get_lasts(t_ast	*input)
{
	t_ast	*ptr;
	ptr = input;
	while(ptr != NULL)
	{
		printf("last_in : %c, last_out : %c\n", input->last_in, input->last_out);
		ptr = ptr->next;
	}
}


int	get_ast(t_var *var)
{
	char	*read;
	t_ast	*input;

	call_pwd(var);
	read = readline(var->pwd_now);
	if (read == NULL)
		return (1);
	input = parser(read, var->our_env);
	get_lasts(input);
	free(read);
	read = NULL;
	if (input == NULL)
	{
		write(1, "plz close quotes.\n", 18);
		return (2);
	}
	var->ast = input;
	var->ast_len = ft_astlen(var->ast);
	if (!var->ast->text[0])
	{
		free_ast_in_var(var);
		return (2);
	}
	return (0);
}
