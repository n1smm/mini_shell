/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:31:56 by tjuvan            #+#    #+#             */
/*   Updated: 2024/09/27 18:34:39 by pgiorgi          ###   ########.fr       */
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
