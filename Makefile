TARGET = minishell
LIBFT = libft.a
GCC = gcc
FLGS = #-g3 -fsanitize=address #-Wall -Wextra -Werror
LR_GY = -lreadline -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include
LR_NK = -lreadline -L /Users/naykim/.brew/opt/readline/lib -I /Users/naykim/.brew/opt/readline/include
DIR_SRCS = ./srcs/
DIR_HEADER = ./header/
DIR_LIBFT = ./libft/
SRCS = action_decider.c b_export.c b_others.c b_unset.c \
	handle_error.c main.c p_actions1.c p_actions2.c p_parse.c p_utils.c \
	utils1.c

all : $(TARGET)
$(TARGET) : $(addprefix $(DIR_SRCS), $(SRCS)) $(addprefix $(DIR_LIBFT), $(LIBFT))
	$(GCC) $(FLGS) $^ -o $@ $(LR_NK)
	#$(GCC) $(FLGS) $^ -o $@ $(LR_GY)
	stty -echoctl

%.o : %.c
	$(GCC) $(FLGS) -c $? -o $@ -I $(DIR_HEADER) $(LR_NK)
	#$(GCC) $(FLGS) -c $? -o $@ -I $(DIR_HEADER) $(LR_GY)


$(addprefix $(DIR_LIBFT), $(LIBFT)) : 
	@make -C $(DIR_LIBFT)
	@make bonus -C $(DIR_LIBFT)

clean : 
	rm -rf $(addprefix $(DIR_SRCS), *.o) $(addprefix $(DIR_LIBFT), *.o)

fclean : clean
	rm -rf $(TARGET) $(addprefix $(DIR_LIBFT), $(LIBFT))

re : clean fclean all

.PHONY : all clean fclean