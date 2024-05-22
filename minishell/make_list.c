/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:44:22 by tjuvan            #+#    #+#             */
/*   Updated: 2024/05/22 15:06:01 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init(char *content, t_token **tail, t_token **head)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->content = content;
	*tail = new_node;
	*head = new_node;
	return (new_node);
}

bool	double_lstadd_front(char *content, t_token **tail)
{
	t_token	*curr;
	t_token	*new;

	new = malloc(sizeof(t_token));
	curr = *tail;
	if (!new)
		return (false);
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

	curr = *head;
	new = malloc(sizeof(t_token));
	if (!new)
		return (false);
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

char *print_token_typ(t_type token_type)
{
	if (token_type == WHITESPACE)
		return ("WHITESPACE");
	if (token_type == NUMBER)
		return ("NUMBER");
	if (token_type == WORD)
		return ("WORD");
	if (token_type == PIPELINE)
		return ("PIPELINE");
	if (token_type == REDIRECT_IN)
		return ("REDIRECT_IN");
	if (token_type == REDIRECT_OUT)
		return ("REDIRECT_OUT");
	if (token_type == EXPAND)
		return ("EXPAND");
	if (token_type == COMMAND)
		return ("COMMAND");
	if (token_type == OPTION)
		return ("OPTION");
	if (token_type == QUOTE)
		return ("QUOTES");
	if (token_type == SINGLE_QUOTE)
		return ("SINGLE_QUOTES");
	return ("INVALID TYPE");
}

void	print_list(t_token *tail)
{
	t_token	*curr;
	int		i;

	i = 0;
	curr = tail;
	printf("list of token types:\n WHITESPACE = 0 \t NUMBER = 1 \t WORD = 2 \n"
			"PIPELINE = 3 \t REDIRECT_IN = 4 \t REDIRECT_OUT = 5 \n"
			"EXPAND = 6 \t COMMAND = 7 \t OPTION = 8");
	while (curr != NULL)
	{
		printf("index of token: %i\t value_token: %s\t type of token: %s\n", i++, curr->content,
			print_token_typ(curr->typ_token));
		curr = curr->next;
	}
}
