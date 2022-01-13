TARGET = minishell
LIBFT = libft.a
GCC = gcc
FLGS = -g #-Wall -Wextra -Werror
DIR_NAYKIM = ./
DIR_HEADER = ../header/
DIR_LIBFT = ../libft/
NAYKIM = n_main.c \
		b_env.c \
		b_cd.c \
		b_pwd.c \
		b_export.c\
		b_unset.c\
		b_echo.c \
		b_exit.c

all : $(TARGET)
$(TARGET) : $(addprefix $(DIR_NAYKIM), $(NAYKIM:.c=.o)) $(addprefix $(DIR_LIBFT), $(LIBFT))
	$(GCC) $(FLGS) $^ -o $@ -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
	stty -echoctl

%.o : %.c
	$(GCC) $(FLGS) -c $? -o $@ -I $(DIR_HEADER) -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include


$(addprefix $(DIR_LIBFT), $(LIBFT)) : 
	make -C $(DIR_LIBFT)
	make bonus -C $(DIR_LIBFT)

clean : 
	rm -rf $(addprefix $(DIR_LIBFT), *.o) $(wildcard *.o)

fclean : clean
	rm -rf $(TARGET) $(addprefix $(DIR_LIBFT), $(LIBFT))

re : clean fclean all

.PHONY : all clean fclean