NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

HEADER = minishell.h

SRC_BUILTINS= $(wildcard ./built_ins/*.c)
EXECUTOR_FILES = ./executor/main_bonus.c ./executor/utils_pipex.c ./executor/utils_bonus_pipex.c
GET_NEXT_LINE_FILES = ./executor/gnl_finished/get_next_line.c ./executor/gnl_finished/get_next_line_utils.c
SRC_FILES = minishell.c expander.c parser.c lexer.c safe_ft.c split_input.c make_list.c free_functions.c path_finder.c executor.c signals.c commands.c \
	$(SRC_BUILTINS) \
	$(EXECUTOR_FILES) $(GET_NEXT_LINE_FILES)

OBJ_FILES = $(SRC_FILES:.c=.o)

LIBFT = ./libft/libft.a
LIBFTDIR = ./libft
# PIPEXDIR = ./pipex-changed

LIBS = -L$(LIBFTDIR) -lreadline -lft
INC = -I$(LIBFTDIR)

all: $(NAME)

$(NAME): $(OBJ_FILES) 
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBS) $(INC) -o $(NAME)

%.o: %.c $(HEADER) $(LIBFT)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

# $(PIPEX):
# 	$(MAKE) -C $(PIPEXDIR) bonus 


	$(MAKE) -C $(LIBFTDIR) clean
	# $(MAKE) -C $(PIPEXDIR) clean
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean
	# $(MAKE) -C $(PIPEXDIR) fclean

re: fclean all

.PHONY: all clean fclean re
