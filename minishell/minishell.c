#include "executor/pipex.h"
int	g_error_code = 0;

static size_t	count_env_vars(char **env)
{
	size_t env_num;

	env_num = 0;
	while (env[env_num])
		env_num++;
	return (env_num);
}

void	ft_init_shell(t_shell **data, char **env)
{
	size_t	i;

	*data = (t_shell *)safe_malloc(sizeof(t_shell));
	//init_t_shell(*data);
	/* (*data)->garbage = NULL; */
	(*data)->garbage.trash = NULL;
	(*data)->num_env_var = count_env_vars(env); //non serve
	(*data)->env = safe_malloc(sizeof(char *) * 1024);
	(*data)->exp = safe_malloc(sizeof(char *) * 1024);
	(*data)->token = safe_malloc(sizeof(char *));
	add_to_garbage(&((*data)->garbage), (*data)->env);
	add_to_garbage(&((*data)->garbage), (*data)->exp);
	add_to_garbage(&((*data)->garbage), (*data)->token);
	add_to_garbage(&((*data)->garbage), *data);
	i = 0;
	while (i < (*data)->num_env_var)
	{
		(*data)->env[i] = ft_strdup(env[i]);
		if (!(*data)->env[i])
		{
			free_garbage(&((*data)->garbage));
			*data = NULL;
			return ;
		}
		add_to_garbage(&((*data)->garbage), (*data)->env[i]);
		i++;
	}
	(*data)->env[(*data)->num_env_var] = NULL;
	i = 0;
	while (i < (*data)->num_env_var)
	{
		(*data)->exp[i] = ft_strdup(env[i]);
		if (!(*data)->exp[i])
		{
			free_garbage(&((*data)->garbage));
			*data = NULL;
			return ;
		}
		add_to_garbage(&((*data)->garbage), (*data)->exp[i]);
		i++;
	}
	(*data)->exp[(*data)->num_env_var] = NULL;
	(*data)->next = NULL;
}

void	ft_init(t_token **tail, t_token **head)
{
	// char	*place_holder;

	if (!tail || !head)
		return ;
	*tail = (t_token *)safe_malloc(sizeof(t_token));
	*head = *tail;
	// add_to_garbage((*tail), (*tail));
	// place_holder = safe_malloc(1);
	// place_holder[0] = 0;
	(*tail)->typ_token = NONPRINTABLE;
	(*tail)->content = NULL;
	(*tail)->special_boy = false;
	(*tail)->next = NULL;
	(*tail)->prev = NULL;
	(*tail)->trash = NULL;
	(*tail)->last_trash = NULL;
}

static char	*prompt_check(t_shell *var)
{
	char	*cwd;
	char	*prompt;
	char	*user;

	user = expander("USER", var, EXPAND);
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

// void cleanup_garbage(t_trash **garbage)
// {
//     t_trash *current;
//     t_trash *next;

//     current = *garbage;
//     while (current)
//     {
//         next = current->next;
//         free(current->content);
//         free(current);
//         current = next;
//     }
//     *garbage = NULL;
// }

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	*prompt;
	t_token	*head;
	t_token	*tail;
	t_shell	*data;
	int 	i;
	//t_trash	*last_trash;

	//last_trash = NULL;
	//t_trash		*garbage;
	tail = NULL;
	head = NULL;
	data = NULL;
	//garbage = NULL;
	argc = argc;
	argv = argv;
	env = env ;
	i = 0;
	//t_input *commands;
	//init_garbage(&garbage);
	ft_init_shell(&data, env);
	ft_init(&tail, &head);
	data->token = tail;
	// add_to_garbage(tail, tail);
	// tail->trash = NULL;
	// head->trash = NULL;
	catch_signals(); //non dà leaks
	while (1)
	{
		//printf("exit:%d", g_exit_status);
		prompt = prompt_check(data);
		input = readline(prompt);
		if (input == NULL)
			break ;
		add_history(input); //non dà leaks
		split_input(input, &tail, &head);
		while (valid_env_var(argv[i]) == 0 && argv[i])
			i = 0;
		parser(&tail, &head, data);
		free_input_prompt(input, prompt);
		if (after_parsy(&tail, &head))
			new_executor(&tail, data, &head);
		printf("\n	PRINT LIST TOKEN :\n\n");
		print_list(tail);
		printf("\n");
		//free_garbage(tail);
		//free_garbage((t_token *) data);
		//free_garbage(head);
		//free_tokens(&tail);
		free_tokens(&tail, &head);
		// printf("%p", tail);
		// rl_clear_history();
		// rl_free_line_state();
		// rl_cleanup_after_signal();
	}
	//printf("\nMinishell è terminato\n");
	free_input_prompt(input, prompt);
	free_garbage(tail);
	//free(tail);
	free_garbage(&(data->garbage));
	// cleanup_garbage(&(tail)->trash);
	//free_garbage(head);
	//free_tokens(&tail);
	//free(data);
	//free(data->var_name);
	//free(data->var_value);
	// free(tail->trash);
	free_tokens_final(&tail, &head);
	printf("CHECK : %p", tail);
	tail = NULL;
	head = NULL;
	rl_clear_history();
	rl_free_line_state();
	rl_cleanup_after_signal();
	return (0);
}
