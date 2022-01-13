TARGET = minishell
LIBFT = libft.a
GCC = gcc
FLGS = -g3 -fsanitize=address #-Wall -Wextra -Werror
DIR_GYEON = ./gyeon/
DIR_SRCS = ./srcs/
DIR_HEADER = ./header/
DIR_LIBFT = ./libft/
GYEON = G_main.c p_parse.c p_actions1.c p_actions2.c p_utils.c action_decider.c
SRCS = utils1.c handle_error.c

all : $(TARGET)
$(TARGET) : $(addprefix $(DIR_GYEON), $(GYEON:.c=.o)) $(addprefix $(DIR_SRCS), $(SRCS)) $(addprefix $(DIR_LIBFT), $(LIBFT))
	$(GCC) $(FLGS) $^ -o $@ -lreadline -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include
	stty -echoctl

%.o : %.c
	$(GCC) $(FLGS) -c $? -o $@ -I $(DIR_HEADER) -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include


$(addprefix $(DIR_LIBFT), $(LIBFT)) : 
	make -C $(DIR_LIBFT)
	make bonus -C $(DIR_LIBFT)

clean : 
	rm -rf $(addprefix $(DIR_SRC), *.o) $(addprefix $(DIR_LIBFT), *.o)

fclean : 
	rm -rf $(TARGET) $(addprefix $(DIR_LIBFT), $(LIBFT))

re : clean fclean all

.PHONY : all clean fclean