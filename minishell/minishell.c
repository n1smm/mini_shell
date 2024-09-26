/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:58:46 by thiew             #+#    #+#             */
/*   Updated: 2024/09/26 17:27:54 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/pipex.h"

int			g_error_code = 0;

void	ft_init(t_token **tail, t_token **head)
{
	if (!tail || !head)
		return ;
	*tail = (t_token *)safe_malloc(sizeof(t_token));
	*head = *tail;
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

static char	*safe_readline(char *prompt, t_shell *data)
{
	char	*input;

	input = readline(prompt);
	if (input == NULL)
	{
		free_here(data, &data->token, NULL);
		exit(EXIT_FAILURE);
	}
	return (input);
}

static void	pars_exec(t_token **tail, t_token **head, t_shell *data)
{
	parser(tail, head, data);
	if (after_parsy(tail, head))
		new_executor(tail, data, head);
	free_tokens(tail, head);
	data->token = *tail;
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	*prompt;
	t_token	*head;
	t_token	*tail;
	t_shell	*data;

	if (argc > 1)
		return (1);
	ft_init_shell(&data, env);
	ft_init(&tail, &head);
	data->token = tail;
	data->i = 0;
	catch_signals();
	while (1)
	{
		prompt = prompt_check(data);
		input = safe_readline(prompt, data);
		add_history(input);
		split_input(input, &tail, &head);
		while (valid_env_var(argv[data->i]) == 0 && argv[data->i])
			data->i = 0;
		free_input_prompt(input, prompt);
		pars_exec(&tail, &head, data);
	}
}
