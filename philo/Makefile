# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 20:28:32 by asoudani          #+#    #+#              #
#    Updated: 2025/04/20 20:46:05 by asoudani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=thread

SRC = philo_utils.c utils.c arg_related.c routine.c initialization.c main.c monitoring.c fork_utils.c

NAME = philo
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

test : fclean all

	clear && ./philo 3 180 80 80

re : fclean all

