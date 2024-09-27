/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:00:39 by thiew             #+#    #+#             */
/*   Updated: 2024/09/26 12:19:24 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_tokens_supp_2(t_token *new_node)
{
	free(new_node);
	new_node = NULL;
}

static void	free_tokens_supp(t_token *new_node, t_token **tail, t_token **head)
{
	new_node->content = NULL;
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->typ_token = NONPRINTABLE;
	new_node->trash = NULL;
	*head = new_node;
	*tail = new_node;
}

void	free_tokens(t_token **tail, t_token **head)
{
	t_token	*curr;
	t_token	*next_node;
	t_token	*new_node;

	while ((*tail)->prev)
		(*tail) = (*tail)->prev;
	if (*tail != NULL)
	{
		curr = *tail;
		while (curr->next != NULL)
		{
			next_node = curr->next;
			free(curr->content);
			free(curr);
			curr = next_node;
		}
		free(curr->content);
		free(curr);
	}
	new_node = safe_malloc(sizeof(t_token));
	if (new_node)
		free_tokens_supp(new_node, tail, head);
	else
		free_tokens_supp_2(new_node);
}

void	free_tokens_final(t_token **tail, t_token **head)
{
	t_token	*curr;
	t_token	*next_node;

	while ((*tail)->prev)
		(*tail) = (*tail)->prev;
	if (*tail != NULL)
	{
		curr = *tail;
		while (curr != NULL)
		{
			next_node = curr->next;
			free(curr->content);
			free(curr);
			curr = next_node;
		}
		free(curr);
		*head = NULL;
		*tail = NULL;
	}
}

void	free_input_prompt(char *input, char *prompt)
{
	if (input)
		free(input);
	if (prompt)
		free(prompt);
}
