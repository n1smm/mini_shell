/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:32:55 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/09/27 18:33:07 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


t_type	quote_init(t_token *tmp, t_token **curr, int *is_quote,
	t_type *mod_type)
{
	t_type	all_quotes_are_equal;

	*curr = tmp->next;
	*is_quote = 0;
	if (*mod_type != WORD)
		all_quotes_are_equal = *mod_type;
	else
		all_quotes_are_equal = tmp->prev->typ_token;
	if (tmp->typ_token == QUOTE)
		*is_quote = 1;
	else
		*is_quote = 2;
	return (all_quotes_are_equal);
}

t_token	*return_node(t_token *curr, t_token *tmp)
{
	if (!curr)
	{
		tmp->typ_token = FALSE_PLACEMENT;
		return (NULL);
	}
	if (tmp->prev && curr->next && is_delimiting_node(tmp->prev)
		&& is_delimiting_node(curr->next))
		return (curr);
	return (curr);
}

void	str_or_word(t_token *curr, t_type *mod_type, int is_quote)
{
	if (curr->typ_token == WORD)
		check_word(curr, mod_type, is_quote);
	else if (curr->typ_token == STRING)
		check_string(curr, mod_type, is_quote);
	else
		curr->typ_token = PRINTABLE;
}

static t_token	*check_quote(t_token **tail, t_token *tmp,
		t_shell *data, t_type *mod_type)
{
	t_token	*curr;
	t_type	all_quotes_are_equal;
	int		is_quote;

	all_quotes_are_equal = quote_init(tmp, &curr, &is_quote, mod_type);
	while (curr && curr->typ_token != tmp->typ_token)
	{
		str_or_word(curr, mod_type, is_quote);
		if (curr->typ_token == EXPAND)
		{
			expand_checker(curr, data);
			if (curr->content[0] == 0)
				delete_node(tail, curr, NULL);
			else
				expand_parser(curr, mod_type);
		}
		curr = curr->next;
	}
	curr = return_node(curr, tmp);
	if (all_quotes_are_equal != NONPRINTABLE)
		*mod_type = all_quotes_are_equal;
	return (curr);
}

void	parsing_tokens(t_token *curr, t_type *mod_type)
{
	if (curr->typ_token == PIPELINE)
		*mod_type = PIPELINE;
	else if (curr->typ_token == REDIRECT_IN)
		*mod_type = REDIRECT_IN;
	else if (curr->typ_token == REDIRECT_IN_DOUBLE)
		*mod_type = REDIRECT_IN_DOUBLE;
	else if (curr->typ_token == REDIRECT_OUT)
		*mod_type = REDIRECT_OUT;
	else if (curr->typ_token == REDIRECT_OUT_DOUBLE)
		*mod_type = REDIRECT_OUT_DOUBLE;
	else if (curr->typ_token == WORD)
		check_word(curr, mod_type, 0);
	else if (curr->typ_token == STRING)
		check_string(curr, mod_type, 0);
}