# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thiew <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/03 12:56:21 by thiew             #+#    #+#              #
#    Updated: 2024/04/06 14:13:13 by tjuvan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror 
NAME = pipex
BONUS_NAME = pipex_bonus
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
	@rm -f fdf_bonus
	@$(MAKE) -C ./final_libft
	$(CC) $(CFLAGS) $(OBJ_MAIN) ./final_libft/libft.a -o $(NAME)

$(BONUS_NAME): $(OBJ_BONUS)
	@rm -f main.o
	@rm -f fdf
	@$(MAKE) -C ./final_libft
	$(CC) $(CFLAGS) $(OBJ_BONUS) ./final_libft/libft.a -o $(BONUS_NAME)

clean:
	$(MAKE) -C ./final_libft fclean
	rm -f $(OBJ_MAIN)
	rm -f $(OBJ_BONUS)
fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)

re: fclean all

