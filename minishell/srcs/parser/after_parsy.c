/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_parsy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:36:54 by tjuvan            #+#    #+#             */
/*   Updated: 2024/09/27 17:44:12 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_empty(t_token **tail)
{
	t_token	*curr;
	bool	empty;

	if (!tail || !(*tail))
		return (1);
	curr = (*tail)->next;
	if (curr && curr->typ_token == PIPELINE)
	{
		printf("invalid placement of: %s\n", curr->content);
		return (0);
	}
	empty = true;
	while (curr)
	{
		if (curr && curr->typ_token != WHITESPACE)
			empty = false;
		curr = curr->next;
	}
	if (empty)
		return (0);
	return (1);
}

int	duplicate_pipe(t_token *curr)
{
	while (curr && curr->typ_token != PIPELINE)
	{
		if (curr->typ_token != WHITESPACE && curr->typ_token != PIPELINE)
			return (0);
		curr = curr->next;
	}
	return (1);
}

int	is_duplicate_node(t_token *curr, t_type type)
{
	if (type == PIPELINE)
	{
		if (duplicate_pipe(curr))
			return (1);
		return (0);
	}
	while (curr && (!is_delimiting_node(curr) || curr->typ_token == WHITESPACE))
	{
		if (!is_delimiting_node(curr) && type != PIPELINE)
			return (0);
		curr = curr->next;
	}
	return (1);
}

int	check_doubles(t_token **tail)
{
	t_token	*curr;
	t_type	type;

	curr = (*tail)->next;
	while (curr)
	{
		if (is_delimiting_node(curr) && curr->typ_token != WHITESPACE)
		{
			type = curr->typ_token;
			curr = curr->next;
			if (is_duplicate_node(curr, type))
			{
				printf("invalid placement of: %s\n", curr->prev->content);
				return (0);
			}
		}
		curr = curr->next;
	}
	return (1);
}

int	after_parsy(t_token **tail, t_token **head)
{
	*head = *head;
	if (!check_empty(tail))
		return (0);
	if (!check_quotes(tail))
		return (0);
	if (!check_eol(tail))
		return (0);
	if (!check_doubles(tail))
		return (0);
	return (1);
}
