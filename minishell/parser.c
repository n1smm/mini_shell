/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:31:56 by tjuvan            #+#    #+#             */
/*   Updated: 2024/08/01 15:37:16 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* is_quote 0 - not iside quotes, is_quote 1 - inside double quotes, is_quote 2 - inside single */
static void	check_string(t_token *curr, t_type *mod_type, int is_quote) // TODO
{
	if ((*mod_type == COMMAND || *mod_type == OPTION)
		&& curr->content[0] == '-')
		curr->typ_token = OPTION;
	else if (*mod_type == REDIRECT_IN)
		curr->typ_token = INFILE;
	else if (*mod_type == REDIRECT_IN_DOUBLE)
		curr->typ_token = LIMITER;
	else if (*mod_type == REDIRECT_OUT_DOUBLE || *mod_type == REDIRECT_OUT)
		curr->typ_token = OUTFILE;
	else if (ft_strchr(curr->content, '$') && is_quote != 2)
		curr->typ_token = EXPAND;
	else if (ft_strchr(curr->content, '/'))
		curr->typ_token = PATH;
	/* else if (*mod_type == WHITESPACE || *mod_type == PIPELINE) */
	/* 	curr->typ_token = FALSE_PLACEMENT; */
	if (curr->typ_token != STRING)
		*mod_type = curr->typ_token;
}

/* there might be more conditions, need to be checked thorouglhy */
static void	check_word(t_token *curr, t_type *mod_type, int is_quote) // TODO
{
	/* there is problem where <<li"mit" mit becomes command */
	if ((*mod_type == WHITESPACE || *mod_type == PIPELINE || *mod_type == INFILE
		|| *mod_type == LIMITER) && is_quote != 1)
		curr->typ_token = COMMAND;
	else if (*mod_type == REDIRECT_IN)
		curr->typ_token = INFILE;
	else if (*mod_type == REDIRECT_IN_DOUBLE)
		curr->typ_token = LIMITER;
	else if (*mod_type == REDIRECT_OUT_DOUBLE || *mod_type == REDIRECT_OUT)
		curr->typ_token = OUTFILE;
	else if (is_quote == 1 || is_quote == 2)
		curr->typ_token = WORD;
	if (curr->typ_token != WORD)
		*mod_type = curr->typ_token;
}

/* quotes need to behave the same as the specific part of grammar they are substituting */
/* that means that if quote is at the start of expression it needs to be considered a command */
/* all of its content is understood as this part of expression */
/* TODO - need to check for this cases ex.(l"s") where i need to treat all as one token */
/* this TODO is resolved by checking all tokens that are not delimited by whitespace */
/* as one bigger token */

static t_token	*check_quote(t_token **tail, t_token *tmp, t_type *mod_type)
{
	t_token	*curr;
	t_type	all_quotes_are_equal;
	int		is_quote;

	curr = tmp->next;
	all_quotes_are_equal = *mod_type;
	if (tmp->typ_token == QUOTE)
		is_quote = 1;
	else
		is_quote = 2;
	while (curr && curr->typ_token != tmp->typ_token)
	{
		if (curr->typ_token == WORD)
			check_word(curr, mod_type, is_quote);
		else if (curr->typ_token == STRING)
			check_string(curr, mod_type, is_quote);
		else
			curr->typ_token = PRINTABLE;
		if (curr->typ_token == EXPAND)
		{
			expand_checker(curr);
			if (curr->content[0] == 0)
				delete_node(tail, curr);
		}

		/* if (curr == tmp->next) */
		/* 	all_quotes_are_equal = curr->typ_token; */
        /* printf("Token type: %s, content: %s  mod_type: %s \n", print_token_typ(curr->typ_token), curr->content, print_token_typ(*mod_type)); */
		curr = curr->next;
	}
	if (!curr)
	{
		tmp->typ_token = FALSE_PLACEMENT;
		return (NULL);
	}
	*tail = *tail;
	/* CHECK FREEING OF QUOTES */
	/* delete_node(tail, tmp); */
	/* delete_node(tail, curr); */
	*mod_type = all_quotes_are_equal;
	return (curr);
}

void	parser(t_token **tail, t_token **head)
{
	t_token	*curr;
	t_type	mod_type;

	curr = (*tail)->next;
	head = head;
	mod_type = WHITESPACE;
	while (curr)
	{
		if (curr->typ_token == QUOTE || curr->typ_token == SINGLE_QUOTE)
		{
			curr = check_quote(tail, curr, &mod_type);
			if (!curr)
				break ;
		}
		else if (curr->typ_token == PIPELINE)
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
		if (curr->typ_token == EXPAND)
		{
			expand_checker(curr);
			if (curr->content[0] == 0)
				delete_node(tail, curr);
		}
        /* printf("Token type: %s, content: %s  mod_type: %s \n", print_token_typ(curr->typ_token), curr->content, print_token_typ(mod_type)); */
		curr = curr->next;
	}
}
