/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:31:56 by tjuvan            #+#    #+#             */
/*   Updated: 2024/09/24 13:01:22 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_string(t_token *curr, t_type *mod_type, int is_quote) // TODO
{
	if (ft_strchr(curr->content, '$') && is_quote != 2)
		curr->typ_token = EXPAND;
	else if ((*mod_type == WHITESPACE || *mod_type == PIPELINE || \
		*mod_type == INFILE || *mod_type == LIMITER || *mod_type == OUTFILE))
	{
		curr->typ_token = COMMAND;
	}
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
	if ((*mod_type == WHITESPACE || *mod_type == PIPELINE || \
		*mod_type == INFILE || *mod_type == LIMITER || *mod_type == OUTFILE))
	{
		curr->typ_token = COMMAND;
	}
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

// static void	c_qu_supp_2(t_token *curr, t_type *type, int is_quote, t_shell *data)
// {
// 	if (curr->typ_token == WORD)
// 		check_word(curr, type, is_quote);
// 	else if (curr->typ_token == STRING)
// 		check_string(curr, type, is_quote);
// 	else
// 		curr->typ_token = PRINTABLE;
// 	if (curr->typ_token == EXPAND)
// 	{
// 		expand_checker(curr, data);
// 		if (curr->content[0] == 0)
// 			delete_node(tail, curr, NULL);
// 		else
// 			expand_parser(curr, type);
// 	}
// }

static t_type	c_qu_supp(t_type *type, int all_quotes_are_equal, t_token *tmp)
{
	if (*type != WORD)
		all_quotes_are_equal = *type;
	else
		all_quotes_are_equal = tmp->prev->typ_token;
	return (all_quotes_are_equal);
}

static int	c_qu_supp_2(t_token *tmp)
{
	int	is_quote;

	is_quote = 0;
	if (tmp->typ_token == QUOTE)
		is_quote = 1;
	else
		is_quote = 2;
	return (is_quote);
}

static void c_qu_supp_3(t_token *curr, t_shell *data, t_token **tail, t_type *type)
{
	expand_checker(curr, data);
	if (curr->content[0] == 0)
		delete_node(tail, curr, NULL);
	else
		expand_parser(curr, type);
}

static t_token *c_qu_supp_4(t_token *tmp)
{
	tmp->typ_token = FALSE_PLACEMENT;
	return (NULL);
}

static t_token	*c_qu_supp_5(t_token *tmp, t_token *curr, t_type all_quotes_are_equal, t_type *type)
{
	if (tmp->prev && curr->next && is_delimiting_node(tmp->prev) \
		&& is_delimiting_node(curr->next))
	{
		return (curr);
	}
	if (all_quotes_are_equal != NONPRINTABLE)
		*type = all_quotes_are_equal;
	return (curr);
}

static t_token	*c_qu(t_token **tail, t_token *tmp, t_shell *data, t_type *type)
{
	t_token	*curr;
	t_type	all_quotes_are_equal;
	int		is_quote;

	curr = tmp->next;
	is_quote = 0;
	all_quotes_are_equal = WHITESPACE;
	all_quotes_are_equal = c_qu_supp(type, all_quotes_are_equal, tmp);
	is_quote = c_qu_supp_2(tmp);
	while (curr && curr->typ_token != tmp->typ_token)
	{
		if (curr->typ_token == WORD)
			check_word(curr, type, is_quote);
		else if (curr->typ_token == STRING)
			check_string(curr, type, is_quote);
		else
			curr->typ_token = PRINTABLE;
		if (curr->typ_token == EXPAND)
			c_qu_supp_3(curr, data, tail, type);
		curr = curr->next;
	}
	if (!curr)
		c_qu_supp_4(tmp);
	*tail = *tail;
	curr = c_qu_supp_5(tmp, curr, all_quotes_are_equal, type);
	return (curr);
}

// static void	parser_supp_2()
// {
	
// }

static t_type	parser_supp(t_token *curr, t_type mod_type)
{
	if (curr->typ_token == PIPELINE)
		mod_type = PIPELINE;
	else if (curr->typ_token == REDIRECT_IN)
		mod_type = REDIRECT_IN;
	else if (curr->typ_token == REDIRECT_IN_DOUBLE)
		mod_type = REDIRECT_IN_DOUBLE;
	else if (curr->typ_token == REDIRECT_OUT)
		mod_type = REDIRECT_OUT;
	else if (curr->typ_token == REDIRECT_OUT_DOUBLE)
		mod_type = REDIRECT_OUT_DOUBLE;
	else if (curr->typ_token == WORD)
		check_word(curr, &mod_type, 0);
	else if (curr->typ_token == STRING)
		check_string(curr, &mod_type, 0);
	return (mod_type);
}

void	parser(t_token **tail, t_token **head, t_shell *data)
{
	t_token	*curr;
	t_token	*tmp;
	t_type	mod_type;

	curr = (*tail)->next;
	head = head;
	mod_type = WHITESPACE;
	while (curr)
	{
		if (curr->typ_token == QUOTE || curr->typ_token == SINGLE_QUOTE)
		{
			if (curr && !is_delimiting_node(curr->prev))
				mod_type = WORD;
			curr = c_qu(tail, curr, data, &mod_type); //DA' SEG FAULT!!
			if (!curr)
				break ;
		}
		else if (curr->typ_token != EXPAND)
			mod_type = parser_supp(curr, mod_type);
		if (curr->typ_token == EXPAND)
		{
			expand_checker(curr, data);
			if (curr && curr->content[0] == 0)
			{
				tmp = curr->prev;
				delete_node2(tail, &curr, head);
				curr = tmp;
			}
			else
				expand_parser(curr, &mod_type);
		}
		if (curr)
			curr = curr->next;
	}
}
