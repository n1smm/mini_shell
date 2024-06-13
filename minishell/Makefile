NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

HEADER = minishell.h

SRC_BUILTINS= $(wildcard ./built_ins/*.c)
SRC_FILES = minishell.c expander.c parser.c lexer.c safe_ft.c split_input.c make_list.c free_functions.c path_finder.c executor.c signals.c $(SRC_BUILTINS)

OBJ_FILES = $(SRC_FILES:.c=.o)

LIBFT = ./libft/libft.a
LIBFTDIR = ./libft

LIBS = -L$(LIBFTDIR) -lreadline -lft
INC = -I$(LIBFTDIR)

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBS) $(INC) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

clean:
	$(MAKE) -C $(LIBFTDIR) clean
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re
