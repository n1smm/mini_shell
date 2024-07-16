NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

HEADER = minishell.h

SRC_BUILTINS= $(wildcard ./built_ins/*.c)

SRC_FILES = ft_ls.c minishell.c expander.c parser.c lexer.c safe_ft.c split_input.c make_list.c free_functions.c path_finder.c executor.c signals.c $(SRC_BUILTINS)

OBJ_FILES = $(SRC_FILES:.c=.o)

LIBFT = ./libft/libft.a
LIBFTDIR = ./libft
PIPEXDIR = ./pipex-changed

LIBS = -L$(LIBFTDIR) -lreadline -lft
INC = -I$(LIBFTDIR) -I$(PIPEXDIR)

all: $(NAME)

$(NAME): $(OBJ_FILES) 
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBS) $(INC) -o $(NAME)
	$(LIBFT) $(PIPEX)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(PIPEX):
	$(MAKE) -C $(PIPEXDIR) bonus 

clean:
	$(MAKE) -C $(LIBFTDIR) clean
	$(MAKE) -C $(PIPEXDIR) clean
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean
	$(MAKE) -C $(PIPEXDIR) fclean

re: fclean all

.PHONY: all clean fclean re
