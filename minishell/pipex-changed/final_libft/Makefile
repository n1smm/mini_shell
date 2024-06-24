# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 09:18:41 by tjuvan            #+#    #+#              #
#    Updated: 2024/02/26 15:48:49 by tjuvan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
SRC_FILES = \
ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
ft_isascii.c ft_isdigit.c ft_isprint.c ft_memcmp.c \
ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
ft_putstr_fd.c ft_putnbr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c \
ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
ft_strncmp.c ft_strrchr.c ft_substr.c ft_tolower.c ft_toupper.c ft_strtrim.c \
ft_memchr.c ft_strnstr.c
#BONUS_FILES = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
#ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
OBJ_FILES = $(SRC_FILES:%.c=%.o)
#OBJ_FILES_BONUS = $(BONUS_FILES:%.c=%.o)
all: $(NAME)

$(NAME): $(OBJ_FILES)
	@ar rcs $(NAME) $(OBJ_FILES)
	@echo "I finished objectifying you"

#bonus: $(OBJ_FILES) $(OBJ_FILES_BONUS)  
#	@ar rcs $(NAME) $(OBJ_FILES) $(OBJ_FILES_BONUS)
#	@echo "I finished objectifying libft"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
#	@echo "what the comp** is this: $<"

test: libft.a
	$(CC) $(CFLAGS) $(xtr) $(prog)  $< -L. -lft 

clean: 
	@rm -f $(OBJ_FILES) $(OBJ_FILES_BONUS)
	@echo "clean your lib_plates"

fclean: clean
	@rm -f $(NAME)
	@echo "clean it real good!(libft)"

re: fclean all
