# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thiew <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/03 12:56:21 by thiew             #+#    #+#              #
#    Updated: 2024/07/09 22:59:47 by thiew            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror 
NAME = pipex
BONUS_NAME = pipex_bonus
# TEST_FILES = ../safe_ft.c ../path_finder.c
SRC_FILES = path_finder.c utils_pipex.c \
			./gnl_finished/get_next_line.c ./gnl_finished/get_next_line_utils.c
SRC_MAIN = main.c $(SRC_FILES)
SRC_BONUS = main_bonus.c utils_bonus_pipex.c $(SRC_FILES)

OBJ_FILES = $(SRC_FILES:%.c=%.o)
OBJ_MAIN = $(SRC_MAIN:%.c=%.o)
OBJ_BONUS = $(SRC_BONUS:%.c=%.o)

all: $(NAME) 

bonus: $(BONUS_NAME) 

$(NAME): $(OBJ_MAIN)
	@rm -f main_bonus.o
	@rm -f pipex_bonus
	$(CC) $(CFLAGS) $(OBJ_MAIN) $(NAME)

$(BONUS_NAME): $(OBJ_BONUS)
	@rm -f main.o
	@rm -f pipex
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(BONUS_NAME)

clean:
	rm -f $(OBJ_MAIN)
	rm -f $(OBJ_BONUS)
fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)

re: fclean all

