TARGET = minishell
LIBFT = libft.a
GCC = gcc
FLGS = -g3 -fsanitize=address #-Wall -Wextra -Werror
DIR_SRCS = ./srcs/
DIR_HEADER = ./header/
DIR_LIBFT = ./libft/
SRCS = action_decider.c b_export.c b_others.c b_unset.c \
	handle_error.c main.c p_actions1.c p_actions2.c p_parse.c p_utils.c \
	utils1.c

all : $(TARGET)
$(TARGET) : $(addprefix $(DIR_GYEON), $(GYEON:.c=.o)) $(addprefix $(DIR_NAYKIM), $(NAYKIM:.c=.o)) $(addprefix $(DIR_SRCS), $(SRCS)) $(addprefix $(DIR_LIBFT), $(LIBFT))
	$(GCC) $(FLGS) $^ -o $@ -lreadline -L /Users/naykim/.brew/opt/readline/lib -I /Users/naykim/.brew/opt/readline/include
	stty -echoctl

%.o : %.c
	$(GCC) $(FLGS) -c $? -o $@ -I $(DIR_HEADER) -L /Users/naykim/.brew/opt/readline/lib -I /Users/naykim/.brew/opt/readline/include


$(addprefix $(DIR_LIBFT), $(LIBFT)) : 
	@make -C $(DIR_LIBFT)
	@make bonus -C $(DIR_LIBFT)

clean : 
	rm -rf $(addprefix $(DIR_SRCS), *.o) $(addprefix $(DIR_GYEON), *.o) $(addprefix $(DIR_NAYKIM), *.o) $(addprefix $(DIR_LIBFT), *.o)

fclean : clean
	rm -rf $(TARGET) $(addprefix $(DIR_LIBFT), $(LIBFT))

re : clean fclean all

.PHONY : all clean fclean