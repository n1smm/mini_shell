NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -o0

HEADER = includes/minishell.h executor/pipex.h includes/structs.h

SRC_BUILTINS= built_ins/cd.c built_ins/env.c built_ins/echo.c built_ins/pwd.c built_ins/unset.c built_ins/exit.c
EXECUTOR_FILES = ./executor/main_bonus.c ./executor/utils_pipex.c ./executor/utils_bonus_pipex.c ./executor/sequence_extraction.c ./executor/utils_mini.c ./executor/check_files.c ./executor/comm_execution.c ./executor/utils_files.c ./executor/utils_rest.c
GET_NEXT_LINE_FILES = ./executor/gnl_finished/get_next_line.c ./executor/gnl_finished/get_next_line_utils.c
SRC_FILES = minishell.c \
	utils_main.c \
	expander.c expander_utils.c\
	parser.c \
	safe_ft.c \
	split_input.c split_input_utils.c \
	make_list.c make_list_utils.c\
	free_functions.c free_functions_utils.c\
	export.c export_utils.c add_to_export.c add_to_env.c\
	path_finder.c \
	signals.c \
	garbage.c \
	after_parsy.c after_parsy_utils.c \
	utils_tokens.c \
	$(SRC_BUILTINS) $(EXECUTOR_FILES) $(GET_NEXT_LINE_FILES)

OBJ_FILES = $(SRC_FILES:.c=.o)

LIBFT = ./libft/libft.a
LIBFTDIR = ./libft
# PIPEXDIR = ./pipex-changed

LIBS = -L$(LIBFTDIR) -lreadline -lft
INC = -I$(LIBFTDIR) -I. -I./executor -I./includes

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBS) $(INC) -o $(NAME)

%.o: %.c $(HEADER) $(LIBFT)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

# $(PIPEX):
# 	$(MAKE) -C $(PIPEXDIR) bonus 

clean:
	$(MAKE) -C $(LIBFTDIR) clean
	# $(MAKE) -C $(PIPEXDIR) clean
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean
	# $(MAKE) -C $(PIPEXDIR) fclean

re: fclean all

.PHONY: all clean fclean re
