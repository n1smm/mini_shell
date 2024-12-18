/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_extraction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:56:46 by tjuvan            #+#    #+#             */
/*   Updated: 2024/09/26 12:56:07 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "pipex.h"

static int	command_len(t_token **tail)
{
	int		i;
	t_token	*curr;

	i = 0;
	curr = *tail;
	while (curr && !is_redirect(curr) && curr->typ_token != PIPELINE)
	{
		if (curr->typ_token == WHITESPACE || curr->typ_token == PRINTABLE
			|| curr->typ_token == NONPRINTABLE)
			i--;
		curr = curr->next;
		i++;
	}
	return (i);
}

static char	**comm_seq_init(t_token **tail)
{
	char	**command_seq;
	int		length;

	length = command_len(tail);
	command_seq = safe_malloc(sizeof(char *) * (length + 1));
	command_seq[length] = 0;
	return (command_seq);
}

static void	free_foo(char **foo, char **command_seq, int i)
{
	if (*foo && *foo[0] != 0)
	{
		command_seq[i++] = ft_strdup(*foo);
	}
	if (*foo)
		free(*foo);
	command_seq[i] = NULL;
}

static void	iterate_till_pipe(t_token **tail, t_token *curr)
{
	while (curr && curr->typ_token != PIPELINE)
		curr = curr->next;
	*tail = curr;
}

char	**seq_extract(t_token **tail)
{
	char	**command_seq;
	char	*foo;
	t_token	*curr;
	int		i;

	i = 0;
	curr = *tail;
	command_seq = comm_seq_init(tail);
	foo = create_empty_string(1);
	while (curr && !is_redirect(curr) && curr->typ_token != PIPELINE)
	{
		if (curr->typ_token != WHITESPACE && curr->typ_token != QUOTE
			&& curr->typ_token != SINGLE_QUOTE)
			foo = join_wrapper(foo, curr->content, 1);
		curr = curr->next;
		if (foo[0] && curr && curr->typ_token == WHITESPACE)
		{
			command_seq[i++] = ft_strdup(foo);
			free(foo);
			foo = create_empty_string(1);
		}
	}
	free_foo(&foo, command_seq, i);
	iterate_till_pipe(tail, curr);
	return (command_seq);
}
