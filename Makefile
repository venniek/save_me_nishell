TARGET = minishell
LIBFT = libft.a
GCC = gcc
FLGS = -Wall -Wextra -Werror
DIR_SRC = ./src/
DIR_HEADER = ./header/
DIR_LIBFT = ./libft/
SRCS = main.c


all : $(TARGET)
$(TARGET) : $(addprefix $(DIR_SRC), $(SRCS:.c=.o)) $(addprefix $(DIR_LIBFT), $(LIBFT))
	$(GCC) $(FLGS) $? -o $@ -lreadline

$(addprefix $(DIR_SRC), %.o) : $(addprefix $(DIR_SRC), %.c)
	$(GCC) $(FLGS) -c $? -o $@ -I $(DIR_HEADER)

$(addprefix $(DIR_LIBFT), $(LIBFT)) : 
	make -C $(DIR_LIBFT)

clean : 
	rm $(addprefix $(DIR_SRC), *.o) $(addprefix $(DIR_LIBFT), *.o)

fclean : 
	rm $(TARGET)

re : clean fclean all

.PHONY : all clean fclean