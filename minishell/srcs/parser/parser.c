/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:31:56 by tjuvan            #+#    #+#             */
/*   Updated: 2024/09/27 18:11:51 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* is_quote 0 - not iside quotes, is_quote 
 * 1 inside double quotes, is_quote 2 - inside single */
static void	check_string(t_token *curr, t_type *mod_type, int is_quote)
{
	if (ft_strchr(curr->content, '$') && is_quote != 2)
		curr->typ_token = EXPAND;
	else if ((*mod_type == WHITESPACE || *mod_type == PIPELINE
			|| *mod_type == INFILE || *mod_type == LIMITER
			|| *mod_type == OUTFILE))
		curr->typ_token = COMMAND;
	else if ((*mod_type == COMMAND || *mod_type == OPTION)
		&& curr->content[0] == '-')
		curr->typ_token = OPTION;
	else if (*mod_type == REDIRECT_IN)
		curr->typ_token = INFILE;
	else if (*mod_type == REDIRECT_IN_DOUBLE)
		curr->typ_token = LIMITER;
	else if (*mod_type == REDIRECT_OUT_DOUBLE || *mod_type == REDIRECT_OUT)
		curr->typ_token = OUTFILE;
	else if (ft_strchr(curr->content, '/'))
		curr->typ_token = PATH;
	if (curr->typ_token != STRING && curr->typ_token != EXPAND)
		*mod_type = curr->typ_token;
}

static void	check_word(t_token *curr, t_type *mod_type, int is_quote)
{
	if ((*mod_type == WHITESPACE || *mod_type == PIPELINE || *mod_type == INFILE
			|| *mod_type == LIMITER || *mod_type == OUTFILE))
		curr->typ_token = COMMAND;
	else if (*mod_type == REDIRECT_IN)
		curr->typ_token = INFILE;
	else if (*mod_type == REDIRECT_IN_DOUBLE)
		curr->typ_token = LIMITER;
	else if (*mod_type == REDIRECT_OUT_DOUBLE || *mod_type == REDIRECT_OUT)
		curr->typ_token = OUTFILE;
	else if (is_quote == 1 || is_quote == 2)
		curr->typ_token = WORD;
	if (curr->typ_token != WORD || is_quote > 0)
		*mod_type = curr->typ_token;
}

static void	expand_parser(t_token *curr, t_type *mod_type)
{
	if (curr->typ_token == WORD)
		check_word(curr, mod_type, 0);
	else if (curr->typ_token == STRING)
		check_string(curr, mod_type, 0);
}

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

int	quote_parsing(t_token **curr, t_type *mod_type,
	t_token **tail, t_shell *data)
{
	if ((*curr)->typ_token == QUOTE || (*curr)->typ_token == SINGLE_QUOTE)
	{
		if ((*curr) && !is_delimiting_node((*curr)->prev))
			*mod_type = WORD;
		*curr = check_quote(tail, *curr, data, mod_type);
		if (!(*curr))
			return (0);
	}
	return (1);
}

void	expand_refurbish(t_token **curr, t_token **tail,
	t_token **head, t_type *mod_type)
{
	t_token	*tmp;

	if (*curr && (*curr)->content[0] == 0)
	{
		tmp = (*curr)->prev;
		delete_node2(tail, curr, head);
		*curr = tmp;
	}
	else
		expand_parser(*curr, mod_type);
}

void	parser(t_token **tail, t_token **head, t_shell *data)
{
	t_token	*curr;
	t_type	mod_type;

	curr = (*tail)->next;
	mod_type = WHITESPACE;
	while (curr)
	{
		if (!quote_parsing(&curr, &mod_type, tail, data))
			break ;
		parsing_tokens(curr, &mod_type);
		if (curr->typ_token == EXPAND)
		{
			expand_checker(curr, data);
			expand_refurbish(&curr, tail, head, &mod_type);
		}
		if (curr)
			curr = curr->next;
	}
}
