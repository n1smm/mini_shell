/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:31:56 by tjuvan            #+#    #+#             */
/*   Updated: 2024/08/18 15:18:20 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* is_quote 0 - not iside quotes, is_quote 1 - inside double quotes, is_quote 2 - inside single */
static void	check_string(t_token *curr, t_type *mod_type, int is_quote) // TODO
{
	if (ft_strchr(curr->content, '$') && is_quote != 2)
		curr->typ_token = EXPAND;
	else if ((*mod_type == WHITESPACE || *mod_type == PIPELINE || *mod_type == INFILE
		|| *mod_type == LIMITER || *mod_type == OUTFILE))// && (is_delimiting_node(curr->prev) || is_quote_node(curr->prev)))// && is_quote != 1)
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
	/* else if (*mod_type == WHITESPACE || *mod_type == PIPELINE) */
	/* 	curr->typ_token = FALSE_PLACEMENT; */
	if (curr->typ_token != STRING && curr->typ_token != EXPAND)
		*mod_type = curr->typ_token;
}

/* there might be more conditions, need to be checked thorouglhy */
static void	check_word(t_token *curr, t_type *mod_type, int is_quote) // TODO
{
	/* there is problem where <<li"mit" mit becomes command */
	if ((*mod_type == WHITESPACE || *mod_type == PIPELINE || *mod_type == INFILE
		|| *mod_type == LIMITER || *mod_type == OUTFILE))// && is_quote != 1)
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

/* static t_type	mod_before_quote(t_type	mod_type) */
/* { */
/* 	t_type	type; */

/* 	if (is_delimiting_type(mod_type)) */
/* 		type = NONPRINTABLE; */
/* 	else */
/* 		type = mod_type; */
/* 	return(type); */
/* } */

static void	expand_parser(t_token *curr, t_type *mod_type)
{
		if (curr->typ_token == WORD)
			check_word(curr, mod_type, 0);
		else if (curr->typ_token == STRING)
			check_string(curr, mod_type, 0);
}

static t_token	*check_quote(t_token **tail, t_token *tmp, t_shell *data, t_type *mod_type)
{
	t_token	*curr;
	t_type	all_quotes_are_equal;
	int		is_quote;

	curr = tmp->next;
	is_quote = 0;
	if (*mod_type != WORD)
		all_quotes_are_equal = *mod_type;// mod_before_quote(*mod_type);
	else
		all_quotes_are_equal = tmp->prev->typ_token;
	if (tmp->typ_token == QUOTE)
		is_quote = 1;
	else
		is_quote = 2;
	/* curr->typ_token = *mod_type; */
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
			expand_checker(curr, data);
			if (curr->content[0] == 0)
				delete_node(tail, curr, NULL);
			else
				expand_parser(curr, mod_type);
		}
		curr = curr->next;
	}
	if (!curr)
	{
		tmp->typ_token = FALSE_PLACEMENT;
		return (NULL);
	}
	*tail = *tail;
	/* if (tmp->prev->typ_token == WHITESPACE) */
	if (tmp->prev && curr->next && is_delimiting_node(tmp->prev) && is_delimiting_node(curr->next))
		return (curr);
	if (all_quotes_are_equal != NONPRINTABLE)// && curr->prev->typ_token != WORD)
		*mod_type = all_quotes_are_equal;
	/* if (curr->next && !is_delimiting_type(curr->next->typ_token)) */
	/* 		*mod_type = tmp->prev->typ_token; */
	return (curr);
}

void	parser(t_token **tail, t_token **head, t_shell *data)
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
			if (curr && !is_delimiting_node(curr->prev))
				mod_type = WORD;
			curr = check_quote(tail, curr, data, &mod_type);
			printf("%s", print_token_typ(mod_type));
			printf("\n");
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
			expand_checker(curr, data);
			if (curr->content[0] == 0)
				delete_node(tail, curr, head);
			else
				expand_parser(curr, &mod_type);
		}
		/* if (mod_type == INFILE && !is_delimiting_node(curr->next)) */
		/* 	mod_type = WORD; */

		/* printf("Token type: %s, content: %s  mod_type: %s \n", print_token_typ(curr->typ_token), curr->content, print_token_typ(mod_type)); */
		curr = curr->next;
	}
}
