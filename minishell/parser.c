/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:40:22 by thiew             #+#    #+#             */
/*   Updated: 2024/05/26 11:34:43 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* 
 <whitespace>
	anytype of whitespace
 <word> 
 	there can be no <witespace> in between
	i can contain only alphabetical characters
<number>
	it contains only numerical characters delimited by whitespace
<string>
	can contain any type of  printable character delimited by whitespace
<pipeline>
	it contains only | and nothing else
<redirect_in>
	it can contain < or <<
<redirect_out>
	It contains > or >>
<quote>
	contains "
<single_quote>
	contains '
<expand>
	it is a single $ followed by a <word> without <whitespace> between
<option>
	is a single or double - followed by <word> 
<path>
	is a <string>
<command>
	is <word> at the start of input or after <pipeline>

THIS LATER WHEN ALL THE ELEMENTS ARE CONSTRUCTED 
 <command> ::= <word> | <word> <option> ... <option>
 			| <word> <expand> | <word> <option> <expand>
			| <word>  <quote> <word> <expand> <quote> |
			| ...
some rules for <command>:
	1st argument is always a <word>
	between <word> and <options> there is always <whitespace>
	there can be <word> <quote><single_quote> at the end of <options>
*/



static void	check_string(t_token *curr, t_type *mod_type) //TODO
{
	if ((*mod_type == COMMAND || *mod_type == OPTION) && curr->content[0] == '-')
		curr->typ_token = OPTION;
	else if (ft_strchr(curr->content, '$') && *mod_type != SINGLE_QUOTE)
		curr->typ_token = EXPAND; // this only says that its a possible expansion case, further check needed
	else if (ft_strchr(curr->content, '/') && *mod_type != SINGLE_QUOTE)
		curr->typ_token = PATH; // the same as with EXPAND
	else if (*mod_type == WHITESPACE || *mod_type == PIPELINE)
		curr->typ_token = FALSE_PLACEMENT;
	if( curr->typ_token != STRING)
		*mod_type = curr->typ_token;
}

/* there might be more conditions, need to be checked thorouglhy */
static void	check_word(t_token *curr, t_type *mod_type) //TODO
{
	if (*mod_type == WHITESPACE || *mod_type == PIPELINE || 
			*mod_type == INFILE || *mod_type == LIMITER)
		curr->typ_token = COMMAND;
	else if (*mod_type == REDIRECT_IN)
		curr->typ_token = INFILE;
	else if (*mod_type == REDIRECT_IN_DOUBLE)
		curr->typ_token = LIMITER;
	else if (*mod_type == REDIRECT_OUT_DOUBLE || *mod_type == REDIRECT_OUT)
		curr->typ_token = OUTFILE;
	else if (*mod_type == QUOTE || *mod_type == SINGLE_QUOTE)
		curr->typ_token = WORD;
	else
		curr->typ_token = FALSE_PLACEMENT; //this might be to
										   //aggressive and can catch 
										   //also completely innocent cases
										   //that didn't hurt anyone!
	if (curr->typ_token != WORD)
		*mod_type = curr->typ_token;
}

/* quotes need to behave the same as the specific part of grammar they are substituting */
/* that means that if quote is at the start of expression it needs to be considered a command */
/* all of its content is understood as this part of expression */
static t_token	*check_quote(t_token *tmp, t_type *mod_type)
{
	t_token	*curr;
	t_type	all_quotes_are_equal;

	curr = tmp->next;
	while(curr->typ_token != tmp->typ_token && curr)
	{
		if (curr->typ_token == WORD)
			check_word(curr, mod_type);
		else if (curr->typ_token == STRING)
			check_string(curr, mod_type);
		else
			curr->typ_token = PRINTABLE;
		if (curr == tmp->next)
			all_quotes_are_equal = curr->typ_token;
		curr = curr->next;
	}
	if (!curr)
		tmp->typ_token = FALSE_PLACEMENT;
	*mod_type = all_quotes_are_equal;
	return (curr);
}

void	parser(t_token **tail, t_token **head)
{
	t_token	*curr;
	t_type	mod_type;

	curr = *tail;
	mod_type = WHITESPACE;
	while (curr)
	{
		if (curr->typ_token == QUOTE || curr->typ_token == SINGLE_QUOTE)
			curr = check_quote(curr, &mod_type);
		else if (curr->typ_token == PIPELINE)
			mod_type = PIPELINE;
		else if (curr->typ_token == REDIRECT_IN)
			mod_type = REDIRECT_IN;
		else if (curr->typ_token == REDIRECT_OUT)
			mod_type = REDIRECT_OUT;
		else if (curr->typ_token == WORD)
			check_word(curr, &mod_type);
		else if (curr->typ_token == NUMBER)
		{
			//TODO
		}
		else if (curr->typ_token == STRING)
			check_string(curr, &mod_type);
		curr = curr->next;
	}

}
