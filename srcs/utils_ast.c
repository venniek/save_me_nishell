/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:59:21 by gyeon             #+#    #+#             */
/*   Updated: 2022/01/26 14:59:24 by gyeon            ###   ########.fr       */
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

int	get_ast(t_var *var)
{
	char	*read;

	call_pwd(var);
	read = readline(var->pwd_now);
	if (read == NULL)
		return (1);
	if (read[0] != '\0')
		add_history(read);
	var->ast = parser(read, var->our_env);
	free(read);
	read = 0;
	if (var->ast == NULL)
	{
		printf_err("minishell: WRONG INPUT\n");
		return (2);
	}
	var->ast_len = ft_astlen(var->ast);
	if (!var->ast->text[0])
	{
		free_ast_in_var(var);
		return (2);
	}
	free(read);
	return (0);
}
