#include "minishell.h"
#include "libft/libft.h"

// void ft_parsing(char *input)
// {
// 	//
// }


void ft_init(t_token **tail, t_token **head)
{
	t_token	*new_node;
	char *place_holder;

	// if (!tail || !head)
	// 	return ;
	*tail = (t_token *)safe_malloc(sizeof(t_token));
	//*head = (t_token *)safe_malloc(sizeof(t_token));
	*head = *tail;
	place_holder = malloc(1);
	place_holder[0] = 0;
	new_node = init(place_holder, tail, head);
	new_node->typ_token = NONPRINTABLE;
	/* (*head)->next = NULL; */
	/* (*tail)->prev = NULL; */
	 
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

void	ft_init_shell(t_shell *status)
{
	status->running = true;
}

int main()
{
	char		*input;
	char		*prompt;
	t_token 	*head;
	t_token 	*tail;
	t_shell		*status;

	tail = NULL;
	head = NULL;
	status = NULL;
//	t_input *commands;
	ft_init(&tail, &head);
	ft_init_shell(status);
	while(status->running == true)
	{
		signal(SIGINT, &sig_handler);
		//sigaction(SIGUSR2, &interactive_mode, 0);
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
		print_list(tail);
		free(input);
		free(prompt);
		free_tokens(&tail, &head, 0);
	}
	free(input);
	free(prompt);
	return(0);
}
