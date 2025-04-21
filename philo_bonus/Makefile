# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/21 16:45:58 by asoudani          #+#    #+#              #
#    Updated: 2025/04/21 17:31:11 by asoudani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET=   "\033[0m"
BLUE=  "\033[1;34m"
GREEN=  "\033[1;32m"
RED=	"\033[1;31m"

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=thread

SRC = main.c cleaner.c actions.c general_utils.c philo_simulation.c argument_related.c inits.c

NAME = philo_bonus
OBJ = $(SRC:.c=.o)
PRINTFD = ../printfd/printfd.a


all: $(NAME)


$(NAME): $(OBJ)
	@echo $(BLUE)"Compiling "$(NAME)"..."$(RESET)
	$(CC) $(CFLAGS) $(OBJ) $(PRINTFD) -o $(NAME)
	@echo $(GREEN)"Compilation done!"$(RESET)

clean:
	@rm -f $(OBJ)
	@echo $(RED)"Object files removed!"$(RESET)

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME)
	@echo $(RED)"Executable removed!"$(RESET)

bonus: all

test : fclean all
	clear
	./philo_bonus 3 180 60 60

re : fclean all
