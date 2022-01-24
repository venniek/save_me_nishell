# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: naykim <naykim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/20 13:49:16 by naykim            #+#    #+#              #
#    Updated: 2022/01/24 16:55:34 by naykim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET = minishell
LIBFT = libft.a
GCC = gcc
FLGS = -g3 -fsanitize=address -Wall -Wextra -Werror
LR_GY = -lreadline -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include
LR_GY_MAC = -lreadline -L /Users/gyeon/.brew/opt/readline/lib -I /Users/gyeon/.brew/opt/readline/include
LR_NK_MAC = -lreadline -L /Users/naykim/.brew/opt/readline/lib -I /Users/naykim/.brew/opt/readline/include
LR_NAYKIM = -lreadline -L /opt/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include
DIR_SRCS = ./srcs/
DIR_HEADER = ./header/
DIR_LIBFT = ./libft/
SRCS = action_decider.c action_decider_sub.c b_export.c b_others.c b_unset.c b_exec.c run_command.c pipe_and_process.c\
	handle_error.c main.c p_actions1.c p_actions2.c p_parse.c p_utils.c p_checkerr.c redirections.c\
	utils_ast.c utils_init.c utils_remove.c utils_free.c utils_other.c utils_parsing.c utils_string.c

all : $(TARGET)
$(TARGET) : $(addprefix $(DIR_SRCS), $(SRCS)) $(addprefix $(DIR_LIBFT), $(LIBFT))
	#$(GCC) $(FLGS) $^ -o $@ $(LR_NK_MAC)
	#$(GCC) $(FLGS) $^ -o $@ $(LR_NAYKIM)
	#$(GCC) $(FLGS) $^ -o $@ $(LR_GY_MAC)
	$(GCC) $(FLGS) $^ -o $@ $(LR_GY)
	stty -echoctl

%.o : %.c
	#$(GCC) $(FLGS) -c $? -o $@ -I $(DIR_HEADER) $(LR_NK_MAC)
	#$(GCC) $(FLGS) -c $? -o $@ -I $(DIR_HEADER) $(LR_NAYKIM)
	#$(GCC) $(FLGS) -c $? -o $@ -I $(DIR_HEADER) $(LR_GY_MAC)
	$(GCC) $(FLGS) -c $? -o $@ -I $(DIR_HEADER) $(LR_GY)


$(addprefix $(DIR_LIBFT), $(LIBFT)) : 
	@make -C $(DIR_LIBFT)
	@make bonus -C $(DIR_LIBFT)

clean : 
	rm -rf $(addprefix $(DIR_SRCS), *.o) $(addprefix $(DIR_LIBFT), *.o)

fclean : clean
	rm -rf $(TARGET) $(addprefix $(DIR_LIBFT), $(LIBFT))

re : clean fclean all

.PHONY : all clean fclean
