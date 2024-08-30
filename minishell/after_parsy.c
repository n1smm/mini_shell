/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_parsy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:36:54 by tjuvan            #+#    #+#             */
/*   Updated: 2024/08/22 19:55:10 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_quotes(t_token **tail)
{
	t_token	*curr;

	curr = *tail;
	while (curr)
	{
		if (curr->typ_token == FALSE_PLACEMENT)
		{
			printf("false placement of: %s", curr->content);
			return (0);
		}
		curr = curr->next;
	}
	return (1);
}

static int	check_after_delimiter(t_token *tmp, t_token *curr, bool *valid)
{
	while (tmp)
	{
		if (!is_delimiting_node(tmp))
			*valid = true;
		tmp = tmp->next;
	}
	if (!(*valid))
	{
		printf("invalid placement of: %s", curr->content);
		return (0);
	}
	return (1);
}


static int	check_eol(t_token **tail)
{
	t_token	*curr;
	t_token	*tmp;
	bool	valid;

	curr = (*tail)->next;
	valid = false;
	while (curr)
	{
		if (is_delimiting_node(curr) && curr->typ_token != WHITESPACE)
		{
			tmp = curr;
			if (!check_after_delimiter(tmp, curr, &valid))
					return (0);
			/* while (tmp && !is_delimiting_node(tmp)) */
			/* { */
			/* 	if (!is_delimiting_node(tmp)) */
			/* 		valid = true; */
			/* 	tmp = tmp->next; */
			/* } */
			/* if (!valid) */
			/* { */
			/* 	printf("invalid placement of: %s", curr->content); */
			/* 	return (0); */
			/* } */
		}
		curr = curr->next;
		valid = false;
	}
	return (1);
}

static int	check_empty(t_token **tail)
{
	t_token	*curr;
	bool	empty;

	curr = (*tail)->next;
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

int	after_parsy(t_token **tail, t_token **head)
{
	*head = *head;
	if (!check_empty(tail))
		return (0);
	if (!check_quotes(tail))
		return (0);
	if (!check_eol(tail))
		return (0);
	return (1);
}
