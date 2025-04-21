SRC = putstrr_fd.c unsigned.c formats.c putcharr_fd.c p_hexa.c upper_hexa.c printfd.c putnbrr_fd.c p_memory.c check_char.c
OBJ = $(SRC:.c=.o)
AR = ar rcs
CFLAGS = -Wall -Wextra -Werror -fPIC
NAME = printfd.a

all : $(NAME)

$(NAME) : $(OBJ)
	$(AR) $(NAME) $(?)
clean :
	rm -f $(OBJ)
fclean : clean
	rm -f $(NAME)
re : fclean all

.PHONY : clean fclean