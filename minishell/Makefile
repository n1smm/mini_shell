NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

HEADER = includes/minishell.h executor/pipex.h includes/structs.h

SRC_BUILTINS= srcs/built_ins/cd.c \
	srcs/built_ins/env.c \
	srcs/built_ins/echo.c \
	srcs/built_ins/pwd.c \
	srcs/built_ins/unset.c \
	srcs/built_ins/unset_exp.c \
	srcs/built_ins/exit.c

EXECUTOR_FILES = ./executor/main_bonus.c \
	./executor/utils_pipex.c \
	./executor/utils_bonus_pipex.c \
	./executor/sequence_extraction.c \
	./executor/utils_mini.c \
	./executor/check_files.c \
	./executor/comm_execution.c \
	./executor/utils_files.c \
	./executor/utils_rest.c

GET_NEXT_LINE_FILES = ./executor/gnl_finished/get_next_line.c \
	./executor/gnl_finished/get_next_line_utils.c

SRC_MAIN = srcs/main/main.c \
	srcs/main/utils_main.c \
	srcs/main/signals.c \
	srcs/main/safe_ft.c

SRC_PARSER = srcs/parser/parser.c \
	srcs/parser/after_parsy.c \
	srcs/parser/after_parsy_utils.c \
	srcs/parser/path_finder.c

SRC_TOKENIZATION = srcs/tokenization/split_input.c \
	srcs/tokenization/split_input_utils.c \
	srcs/tokenization/make_list.c \
	srcs/tokenization/make_list_utils.c \
	srcs/tokenization/utils_tokens.c

SRC_EXPANDER = srcs/expander/expander.c \
	srcs/expander/expander_utils.c

SRC_EXPORT = srcs/export/export.c \
	srcs/export/export_utils.c \
	srcs/export/add_to_export.c \
	srcs/export/add_to_env.c

SRC_CLEANUP = srcs/cleanup/free_functions.c \
	srcs/cleanup/free_functions_utils.c \
	srcs/cleanup/garbage.c

SRC_FILES = $(SRC_MAIN) $(SRC_EXPANDER) $(SRC_PARSER) \
	$(SRC_TOKENIZATION) $(SRC_EXPORT) $(SRC_CLEANUP) \
	$(SRC_BUILTINS) $(EXECUTOR_FILES) $(GET_NEXT_LINE_FILES)

OBJ_FILES = $(SRC_FILES:.c=.o)

LIBFT = ./libft/libft.a
LIBFTDIR = ./libft

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
