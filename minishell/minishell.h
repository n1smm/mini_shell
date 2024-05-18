#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <limits.h>
#include <stdio.h>
#include <stddef.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

typedef struct s_input {
	char **cmds;
}	t_input;

typedef enum cmds{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	NOT_VALID
} t_cmds;

void ft_lexer(char *input);
void *safe_malloc(size_t size);