/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:44:22 by tjuvan            #+#    #+#             */
/*   Updated: 2024/05/21 14:42:12 by thiew            ###   ########.fr       */
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
		printf("index of token: %i\t value_token: %s\t type of token: %i\n", i++, curr->content,
			curr->typ_token);
		curr = curr->next;
	}
}
