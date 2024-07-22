/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_extraction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:56:46 by tjuvan            #+#    #+#             */
/*   Updated: 2024/07/22 18:43:18 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "pipex.h"

static int	command_len(t_token **tail)
{
	int	i;
	t_token	*curr;

	i = 0;
	curr = *tail;
	while (CURRENT_COMMAND)
	{
		if ( curr->typ_token == WHITESPACE || curr->typ_token == PRINTABLE || curr->typ_token == NONPRINTABLE)
			i--;
		curr = curr->next;
		i++;
	}
	return(i);
}	

static char	**comm_seq_init(t_token **tail)
{
	char	**command_seq;
	int		length;

	length = command_len(tail);
	printf("length: %d \n", length);
	command_seq = safe_malloc(sizeof(char *) * (length + 1));
	command_seq[length] = 0;
	return (command_seq);
}

char **seq_extract(t_token **tail)
{
	char	**command_seq;
	char	*foo;
	t_token	*curr;
	int		i;

	i = 0;
	curr = *tail;
	command_seq = comm_seq_init(tail);
	foo = create_empty_string(1);
	while (CURRENT_COMMAND)
	{
		if(curr->typ_token != WHITESPACE)
			foo = join_wrapper(foo, curr->content, 1);
		curr = curr->next;
		if (curr  && curr->typ_token == WHITESPACE)
		{
			command_seq[i++] = ft_strdup(foo);
			free(foo);
			foo = create_empty_string(1);
		}
	}
	if (foo && foo[0] != 0 )
		command_seq[i++] = ft_strdup(foo);
	if (foo)
		free(foo);
	*tail = curr;
	command_seq[i] = NULL;
	return (command_seq);
}
