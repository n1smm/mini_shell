#include "minishell.h"
#include "libft/libft.h"
#include "executor/pipex.h"

static size_t	count_env_vars(char **env)
{
	size_t env_num;

	env_num = 0;
	while(env[env_num])
		env_num++;
	return(env_num);
}

void	ft_init_shell(t_shell **data, char **env)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	*data = safe_malloc(sizeof(t_shell));
	(*data)->trash = NULL;
	add_to_garbage((t_token *)(*data), *data);
	(*data)->num_env_var = count_env_vars(env);
	
	(*data)->env = safe_malloc(sizeof(char *) * ((*data)->num_env_var + 1));
	add_to_garbage((t_token *)(*data), (*data)->env);
	while (i < (*data)->num_env_var)
	{
		(*data)->env[i] = ft_strdup(env[i]);
		if (!(*data)->env)
		{
			while(j < i)
			{
				free((*data)->env[j]);
				j++;
			}
			free((*data)->env);
			free(data);
			return ;
		}
		i++;
		add_to_garbage((t_token *)(*data), (*data)->env[i]);
	}
	(*data)->env[(*data)->num_env_var] = NULL;
	(*data)->next = NULL;
}

void ft_init(t_token **tail, t_token **head)
{
	if (!tail || !head)
		return ;

	char *place_holder;

	*tail = (t_token *)safe_malloc(sizeof(t_token));
	*head = *tail;
	place_holder = safe_malloc(1);
	place_holder[0] = 0;
	(*tail)->typ_token = NONPRINTABLE;
	(*tail)->content = place_holder;
	(*tail)->next = NULL;
	(*tail)->prev = NULL;
	(*tail)->trash = NULL;
	add_to_garbage(*tail, *tail);
	add_to_garbage(*tail, place_holder);
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
	//t_shell		*data;
//	t_trash		*garbage;

	tail = NULL;
	head = NULL;
	//data = NULL;
//	garbage = NULL;
	argc = argc;
	argv = argv;
	env = env ;
	//t_input *commands;
	//init_garbage(garbage);
	//ft_init_shell(&data, env);
	ft_init(&tail, &head);
	while(1)
	{
		catch_signals(); //non dà leaks
		//printf("exit:%d", g_exit_status);
		prompt = prompt_check();
		input = readline(prompt);
		if (!input || ft_strncmp(input, "exit", 5) == 0)
		{
			// free(prompt);
			// free(input);
			break ;
		}
		add_history(input); //non dà leaks
		//split_input(input, &tail, &head);
		//parser(&tail, &head);

		//ft_executor(data, &tail, input, env);
		//executor(&tail, env);

		// printf("\n	PRINT LIST TOKEN :\n\n"),
		// print_list(tail);
		// printf("\n");
		free(input);
		free(prompt);
		if (tail)
		{
			free_garbage(tail);
			free(tail);
			tail = NULL;
			head = NULL;
		}
		//free_tokens(&tail, &head, 0);
	}
	free(input);
	free(prompt);
	free_garbage(tail);
	free(tail);
	tail = NULL;
	head = NULL;
	rl_clear_history();
	rl_free_line_state();
	rl_cleanup_after_signal();
	return(0);
}
