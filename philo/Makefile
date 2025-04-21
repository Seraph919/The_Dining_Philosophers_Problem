# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 20:28:32 by asoudani          #+#    #+#              #
#    Updated: 2025/04/21 17:41:48 by asoudani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET=   "\033[0m"
BLUE=  "\033[1;34m"
GREEN=  "\033[1;32m"
RED=	"\033[1;31m"

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=thread

SRC = philo_utils.c utils.c arg_related.c routine.c initialization.c main.c monitoring.c fork_utils.c
PRINTFD = ../printfd/printfd.a

NAME = philo
OBJ = $(SRC:.c=.o)

all:  $(NAME)

$(NAME): $(OBJ)
	@echo $(BLUE)"Compiling "$(NAME)"..."$(RESET)
	$(CC) $(CFLAGS) $(OBJ) $(PRINTFD) -o $(NAME)
	@echo $(GREEN)"The program is ready to run!"$(RESET)

clean:
	@rm -f $(OBJ)
	@echo $(RED)"Object files removed!"$(RESET)

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME)
	@echo $(RED)"Executable removed!"$(RESET)

test : fclean all

	clear && ./philo 3 180 80 80

re : fclean all

