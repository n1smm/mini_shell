/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_parsy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:36:54 by tjuvan            #+#    #+#             */
/*   Updated: 2024/08/01 17:47:07 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_node(t_token *tmp, t_type type, char *quoted_string)
{
	t_token	*curr;

	if (is_delimiting_node(tmp))
	{
		curr = tmp->next;
		curr->content = join_wrapper(curr->content, quoted_string, 2);
		curr->typ_token = type;
	}
	else
	{
		curr = tmp;
		curr->content = join_wrapper(curr->content, quoted_string, 2);
		curr->typ_token = type;
	}
}
		
void	delete_quoted_nodes(t_token **tmp, t_token *end, char **quoted_string)
{
	t_token	*curr;

	curr = *tmp;
	while (curr != end)
	{
		delete_node(tmp, curr);
		curr = *tmp;
	}
	free(quoted_string);
}
		

void	after_parsy(t_token **tail, t_token **head)
{
	t_token	*curr;
	t_token	*tmp;
	t_type	type;
	char	*quoted_string;

	*head = *head;
	curr = *tail;
	quoted_string = create_empty_string(1);
	while (curr)
	{
		if (curr->typ_token == QUOTE || curr->typ_token == SINGLE_QUOTE)
		{
			tmp = curr->prev;
			tmp->special_boy = true;
			curr = curr->next;
			if (is_delimiting_node(tmp))
				type = curr->typ_token;
			else
				type = tmp->typ_token;
			while (curr && curr->typ_token != tmp->next->typ_token)
			{
				quoted_string = join_wrapper(quoted_string, curr->content, 1);
				curr = curr->next;
			}
			change_node(tmp, type, quoted_string);
			delete_quoted_nodes(&tmp, curr, &quoted_string);
			curr = tmp;
		}
		curr = curr->next;
	}
}
