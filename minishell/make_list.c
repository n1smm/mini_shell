/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:44:22 by tjuvan            #+#    #+#             */
/*   Updated: 2024/07/23 17:13:47 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init(char *content, t_token **tail, t_token **head)
{
	t_token	*new_node;

	new_node = safe_malloc(sizeof(t_token));
	/* if (!new_node) */
	/* 	return (NULL); */
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->content = content;
	new_node->typ_token = 0;
	*tail = new_node;
	*head = new_node;
	return (new_node);
}

bool	double_lstadd_front(char *content, t_token **tail)
{
	t_token	*curr;
	t_token	*new;

	new = safe_malloc(sizeof(t_token));
	curr = *tail;
	/* if (!new) */
	/* 	return (false); */
	if (*tail == NULL)
	{
		free(new);
		return (-1);
	}
	new->content = content;
	new->next = curr;
	curr->prev = new;
	*tail = new;
	return (true);
}

bool	double_lstadd_back(char *content, t_token **head)
{
	t_token	*curr;
	t_token	*new;

	if (!head)
		return (-1);
	curr = *head;
	new = safe_malloc(sizeof(t_token));
	if (*head == NULL)
	{
		free(new);
		return (-1);
	}
	new->content = content;
	new->next = NULL;
	curr->next = new;
	new->prev = curr;
	*head = new;
	return (true);
}

void delete_node(t_token **tail, t_token *del)
{
    if (*tail == NULL || del == NULL)
        return;
    if (*tail == del)
        *tail = del->next;
    if (del->next != NULL)
        del->next->prev = del->prev;
    if (del->prev != NULL)
	{
        del->prev->next = del->next;
	}
	del->next = NULL;
	del->prev = NULL;
	free(del);
	del = NULL;
    return;
}

int	find_token(t_token *tail, t_type type)
{
	t_token *curr;

	curr = tail;
	while (curr)
	{
		if (curr->typ_token == type)
			return (1);
		curr = curr->next;
	}
	return(0);	
}

t_token *use_token(t_token **tail, t_type type)
{
	while(*tail)
	{
		if ((*tail)->typ_token == type)
			return (*tail);
		*tail = (*tail)->next;
	}
	return (NULL);
}

char *print_token_typ(t_type token_type)
{
	if (token_type == WHITESPACE)
		return ("WHITESPACE");
	else if (token_type == NONPRINTABLE)
		return ("NONPRINTABLE");
	else if (token_type == WORD)
		return ("WORD");
	else if (token_type == STRING)
		return ("STRING");
	else if (token_type == PIPELINE)
		return ("PIPELINE");
	else if (token_type == REDIRECT_IN)
		return ("REDIRECT_IN");
	else if (token_type == REDIRECT_IN_DOUBLE)
		return ("REDIRECT_IN_DOUBLE");
	else if (token_type == REDIRECT_OUT)
		return ("REDIRECT_OUT");
	else if (token_type == REDIRECT_OUT_DOUBLE)
		return ("REDIRECT_OUT_DOUBLE");
	else if (token_type == EXPAND)
		return ("EXPAND");
	else if (token_type == PATH)
		return ("PATH");
	else if (token_type == COMMAND)
		return ("COMMAND");
	else if (token_type == OPTION)
		return ("OPTION");
	else if (token_type == QUOTE)
		return ("QUOTES");
	else if (token_type == SINGLE_QUOTE)
		return ("SINGLE_QUOTES");
	else if (token_type == INFILE)
		return ("INFILE");
	else if (token_type == OUTFILE)
		return ("OUTFILE");
	else if (token_type == LIMITER)
		return ("LIMITER");
	else if (token_type == PRINTABLE)
		return ("PRINTABLE");
	else if (token_type == FALSE_PLACEMENT)
		return ("FALSE_PLACEMENT");
	return ("INVALID TYPE");
}

void	print_list(t_token *tail)
{
	t_token	*curr;
	int		i;

	i = 0;
	curr = tail;
	while (curr != NULL)
	{
		printf("index of token: %i\t value_token: %s\t type of token: %s\n", i++, curr->content,
			print_token_typ(curr->typ_token));
		curr = curr->next;
	}
}
