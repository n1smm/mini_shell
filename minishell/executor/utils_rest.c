/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:16:53 by thiew             #+#    #+#             */
/*   Updated: 2024/09/23 10:30:17 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "pipex.h"

static void	check_it_out(t_token *curr, int *pipe, int *command)
{
	while (curr)
	{
		if (curr->typ_token == PIPELINE)
			*pipe = 1;
		else if (*pipe == 1 && curr->typ_token != PIPELINE
			&& curr->typ_token != WHITESPACE)
			*command = 1;
		curr = curr->next;
	}
}

int	check_pipe(t_token **tail, t_type file_type[])
{
	t_token	*curr;
	int		pipe;
	int		command;
	int		i;

	curr = *tail;
	pipe = 0;
	command = 0;
	i = -1;
	check_it_out(curr, &pipe, &command);
	while (file_type[++i] != NONPRINTABLE)
	{
		if (file_type[i] == REDIRECT_OUT || file_type[i] == REDIRECT_OUT_DOUBLE)
			command = 0;
	}
	if (pipe == 1 && command == 1)
		return (1);
	if (pipe == 1 && command == 0)
		return (-1);
	return (0);
}
