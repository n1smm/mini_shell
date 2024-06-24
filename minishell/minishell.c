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

int main(int argc, char **argv, char **env)
{
	char		*input;
	char		*prompt;
	t_token 	*head;
	t_token 	*tail;

	tail = NULL;
	head = NULL;
	argc = argc;
	argv = argv;
	env = env ;
	//t_input *commands;
	ft_init(&tail, &head);
	while(1)
	{
		catch_signals();
		//printf("exit:%d", g_exit_status);
		prompt = prompt_check();
		input = readline(prompt);
		if (!input || ft_strncmp(input, "exit", 5) == 0)
			break ;
		add_history(input);
		//ft_parsing(input);
		//printf("\n");
		split_input(input, &tail, &head);
		parser(&tail, &head);

		ft_executor(&tail);

		print_list(tail);
		free(input);
		free(prompt);
		//free_tokens(&tail, &head, 0);
	}
	free(input);
	free(prompt);
	return(0);
}
