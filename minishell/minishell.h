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
	char **tokens;
}	t_input;

typedef struct	s_token 
{
	t_type	typ_token;
	/* void 	*value; */
	char 	*value;
	long 	value;
	t_token *next;
	t_token *previous;
} 				t_token;


typedef struct	s_trash 
{
	void *content;
	t_trash *next;
}				t_trash;

}
typedef enum	s_type{
	DIGIT,
	ALPHA,
	NUMBER,
	WORD,
	PIPELINE,
	REDIRECT,
	EXPAND,
	COMMAND,
	OPTION,
} 				t_type;

/* lexer */
void lexer_main(char *input);
/* safe_functions */
void *safe_malloc(size_t size);
