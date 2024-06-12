#include "minishell.h"
#include "libft/libft.h"

// void ft_parsing(char *input)
// {
// 	//
// }


void ft_init(t_token **tail, t_token **head)
{
	// if (!tail || !head)
	// 	return ;
	*tail = (t_token *)safe_malloc(sizeof(t_token));
	//*head = (t_token *)safe_malloc(sizeof(t_token));
	*head = *tail;
	(*head)->next = NULL;
	(*tail)->prev = NULL;
}

static char *prompt_check(void)
{
	char 	*cwd;
	char	*prompt;
	char	*user;

	user = expander("USER", EXPAND);
	cwd = safe_malloc(1024);
	if (getcwd(cwd, 1024) != NULL && user != NULL)
	{
		user = join_wrapper("Minishell-", user, 2);
		user = join_wrapper(user, ": ", 1);
		cwd = join_wrapper(user, cwd, 3);
		prompt = join_wrapper(cwd, "$ ", 1);
	}
	else
	{
		free(cwd);
		free(user);
		prompt = strdup("Minishell$:");
	}
	return (prompt);
}

int main()
{
	char	*input;
	char	*prompt;
	t_token *head;
	t_token *tail;

	tail = NULL;
	head = NULL;
//	t_input *commands;
	ft_init(&tail, &head);
	while(1)
	{
		sigaction(SIGUSR1, &interactive_mode, 0);
		sigaction(SIGUSR2, &interactive_mode, 0);
		prompt = prompt_check();
		input = readline(prompt);
		add_history(input);
		//ft_parsing(input);
		//printf("\n");
		split_input(input, &tail, &head);
		parser(&tail, &head);
		//printf("%d", (*tail)->typ_token);
		//ft_lexer(input);
		//ft_executor(&tail);
		if (ft_strncmp(input, "exit", 5) == 0)
		 	break;
		free(input);
		free(prompt);
	}
	print_list(tail);
	free(input);
	free(prompt);
	return(0);
}
