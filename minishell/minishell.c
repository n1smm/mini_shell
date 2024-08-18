#include "executor/pipex.h"

static size_t	count_env_vars(char **env)
{
	size_t env_num;

	env_num = 0;
	while (env[env_num])
		env_num++;
	return (env_num);
}

// void init_t_shell(t_shell *shell)
// {
//     shell->trash = NULL;
//     shell->num_env_var = 0;
//     shell->env = NULL;
//     shell->next = NULL;
// }

void	ft_init_garbage(t_token **tail, t_trash **trash)
{
	(*trash) = safe_malloc(sizeof(t_trash));
	(*trash)->content = NULL;
	(*trash)->next= NULL;
	(*tail)->trash = (*trash);
	//add_to_garbage((*tail)->trash, (*trash));

}

void	ft_init_shell(t_shell **data, char **env, t_token **tail)
{
	size_t	i;

	*data = (t_shell *)safe_malloc(sizeof(t_shell));
	tail =tail;
	// add_to_garbage((*tail)->trash, *data);
	//init_t_shell(*data);
	(*data)->trash = NULL;
	(*data)->num_env_var = count_env_vars(env);
	(*data)->env = safe_malloc(sizeof(char *) * 1024);
	i = 0;
	while (i < (*data)->num_env_var)
	{
		(*data)->env[i] = ft_strdup(env[i]);
		if (!(*data)->env[i])
		{
			// while (i > 0)
			// {
			// 	free((*data)->env[--i]);
			// }
			// free((*data)->env);
			// free(*data);
			// free_garbage((*tail)->trash);
			*data = NULL;
			return ;
		}
		// add_to_garbage((*tail)->trash, (*data)->env[i]);
		i++;
	}
	// add_to_garbage((*tail)->trash, (*data)->env);
	(*data)->env[(*data)->num_env_var] = NULL;
	(*data)->next = NULL;
	// add_to_garbage((*tail)->trash, (*data));
}

void	ft_init(t_token **tail, t_token **head, t_trash *garbage)
{
	char	*place_holder;

	if (!tail || !head)
		return ;
	*tail = (t_token *)safe_malloc(sizeof(t_token));
	*head = *tail;
	place_holder = safe_malloc(1);
	place_holder[0] = 0;
	(*tail)->typ_token = NONPRINTABLE;
	(*tail)->content = place_holder;
	(*tail)->special_boy = false;
	(*tail)->next = NULL;
	(*tail)->prev = NULL;
	(*tail)->trash = NULL;
	add_to_garbage(garbage, *tail);
	//add_to_garbage((*tail)->trash, *head);
	add_to_garbage(garbage, place_holder);
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

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	*prompt;
	t_token	*head;
	t_token	*tail;
	t_shell	*data;
	int 	i;
	t_trash		*garbage;
	tail = NULL;
	head = NULL;
	data = NULL;
	garbage = NULL;
	argc = argc;
	argv = argv;
	env = env ;
	i = 0;
	//t_input *commands;
	ft_init(&tail, &head, garbage);
	ft_init_garbage(&tail, &garbage);
	ft_init_shell(&data, env, &tail);
	tail->trash = NULL;
	catch_signals(); //non dà leaks
	while (1)
	{
		//printf("exit:%d", g_exit_status);
		prompt = prompt_check(data);
		input = readline(prompt);
		if (!input || ft_strncmp(input, "exit", 5) == 0)
		{
			//free_input_prompt(input, prompt);
			break ;
		}
		add_history(input); //non dà leaks
		split_input(input, &tail, &head);
		while (valid_env_var(argv[i]) == 0 && argv[i])
		i = 0;
		parser(&tail, &head, data);
		//ft_executor(data, &tail, input, env);
		//executor(&tail, env);
		new_executor(&tail, data, &head);
		 printf("\n	PRINT LIST TOKEN :\n\n"),
		 print_list(tail);
		 printf("\n");
		free_input_prompt(input, prompt);
		//free_garbage(tail->trash);
		//free_garbage((t_token *) data);
		//free_garbage(head);
		//free_tokens(&tail);
		free_tokens(&tail, &head, 0);

		// rl_clear_history();
		// rl_free_line_state();
		// rl_cleanup_after_signal();
	}
	//printf("\nMinishell è terminato\n");
	free_input_prompt(input, prompt);
	free_garbage(tail->trash);
	free_garbage(garbage->content);
	//free_garbage(tail->trash->content);
	//free_garbage((t_token *) data);
	//free_garbage(head);
	//free_tokens(&tail);
	free_garbage(garbage);
	for(int i = 0; data->env[i]; i++)
	{
		free(data->env[i]);
	}
	free(data->env);
	free(data);
	free(tail->trash);
	//free(garbage);
	//free(data->var_name);
	//free(data->var_value);
	free_tokens(&tail, &head, 0);
	rl_clear_history();
	rl_free_line_state();
	rl_cleanup_after_signal();
	return (0);
}

// void	ft_init_shell(t_shell **data, char **env)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	j = 0;
// 	*data = safe_malloc(sizeof(t_shell));
// 	(*data)->trash = NULL;
// 	add_to_garbage((t_token *)(*data), *data);
// 	(*data)->num_env_var = count_env_vars(env);
// 	(*data)->env = safe_malloc(sizeof(char *) * ((*data)->num_env_var + 1));
// 	add_to_garbage((t_token *)(*data), (*data)->env);
// 	while (i < (*data)->num_env_var)
// 	{
// 		(*data)->env[i] = ft_strdup(env[i]);
// 		if (!(*data)->env)
// 		{
// 			while(j < i)
// 			{
// 				free((*data)->env[j]);
// 				j++;
// 			}
// 			free((*data)->env);
// 			free(data);
// 			return ;
// 		}
// 		i++;
// 		add_to_garbage((t_token *)(*data), (*data)->env[i]);
// 	}
// 	(*data)->env[(*data)->num_env_var] = NULL;
// 	(*data)->next = NULL;
// }
