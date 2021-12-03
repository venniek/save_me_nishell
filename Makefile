TARGET = minishell
LIBFT = libft.a
GCC = gcc
FLGS = -Wall -Wextra -Werror
DIR_SRC = ./src/
DIR_HEADER = ./header/
DIR_LIBFT = ./libft/
SRCS = ./main.c


all : $(TARGET)
$(TARGET) : $(addprefix $(DIR_SRC), $(SRCS:.c=.o)), $(LIBFT)
	$(GCC) $(FLGS) $? -o $@

$(addprefix $(DIR_SRC), *.o) : $(addprefix $(DIR_SRC), *.c)
	$(GCC) $(FLGS) -c $? -I $(DIR_HEADER)

$(LIBFT) : 
	make -c $(DIR_LIBFT)

clean : 
	rm $(addprefix $(DIR_SRC), *.o) $(addprefix $(DIR_LIBFT), *.o)

fclean : 
	rm $(TARGET)

.PHONY : all clean fclean