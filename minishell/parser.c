/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:40:22 by thiew             #+#    #+#             */
/*   Updated: 2024/05/26 12:46:55 by tjuvan           ###   ########.fr       */
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

static void	check_string(t_token *curr, t_type *mod_type) // TODO
{
	if ((*mod_type == COMMAND || *mod_type == OPTION)
		&& curr->content[0] == '-')
		curr->typ_token = OPTION;
	else if (ft_strchr(curr->content, '$') && *mod_type != SINGLE_QUOTE)
		curr->typ_token = EXPAND;
			// this only says that its a possible expansion case,
			//further check needed
	else if (ft_strchr(curr->content, '/') && *mod_type != SINGLE_QUOTE)
		curr->typ_token = PATH; // the same as with EXPAND
	else if (*mod_type == WHITESPACE || *mod_type == PIPELINE)
		curr->typ_token = FALSE_PLACEMENT;
	if (curr->typ_token != STRING)
		*mod_type = curr->typ_token;
}

/* there might be more conditions, need to be checked thorouglhy */
static void	check_word(t_token *curr, t_type *mod_type) // TODO
{
	if (*mod_type == WHITESPACE || *mod_type == PIPELINE || *mod_type == INFILE
		|| *mod_type == LIMITER)
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
		curr->typ_token = FALSE_PLACEMENT; // this might be to
											// aggressive and can catch
											// also completely innocent cases
											// that didn't hurt anyone!
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
	all_quotes_are_equal = *mod_type;
	while (curr && curr->typ_token != tmp->typ_token)
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
	{
		tmp->typ_token = FALSE_PLACEMENT;
		return (NULL);
	}
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
		{
			curr = check_quote(curr, &mod_type);
			if (!curr)
				break ;
		}
		else if (curr->typ_token == PIPELINE)
			mod_type = PIPELINE;
		else if (curr->typ_token == REDIRECT_IN)
			mod_type = REDIRECT_IN;
		else if (curr->typ_token == REDIRECT_OUT)
			mod_type = REDIRECT_OUT;
		else if (curr->typ_token == WORD)
			check_word(curr, &mod_type);
		else if (curr->typ_token == STRING)
			check_string(curr, &mod_type);
		curr = curr->next;
	}
}

// Helper function to create a new token
t_token *create_token(t_type typ_token, char *content) {
    t_token *new_token = (t_token *)malloc(sizeof(t_token));
    new_token->typ_token = typ_token;
    new_token->content = strdup(content);
    new_token->next = NULL;
    new_token->prev = NULL;
    return new_token;
}

// Helper function to print the tokens
void print_tokens(t_token *head) {
    t_token *curr = head;
    while (curr) {
        printf("Token type: %d, content: %s\n", curr->typ_token, curr->content);
        curr = curr->next;
    }
}

// Main function for testing
int main() {

  // Create a list of tokens for testing
    t_token *token1 = create_token(WORD, "ls");
    t_token *token2 = create_token(WHITESPACE, " ");
    t_token *token3 = create_token(STRING, "/etc/passwd");
    t_token *token4 = create_token(WHITESPACE, " ");
    t_token *token5 = create_token(PIPELINE, "|");
    t_token *token6 = create_token(WHITESPACE, " ");
    t_token *token7 = create_token(WORD, "echo");
    t_token *token8 = create_token(WHITESPACE, " ");
    t_token *token9 = create_token(QUOTE, "\"");
    t_token *token10 = create_token(WHITESPACE, " ");
    t_token *token11 = create_token(WORD, "hello");
    t_token *token12 = create_token(WHITESPACE, " ");
    t_token *token13 = create_token(STRING, "$USER");
    t_token *token14 = create_token(WHITESPACE, " ");
    t_token *token15 = create_token(STRING, "/this/is/not/a/path");
    t_token *token16 = create_token(QUOTE, "\"");

    // Link tokens
    token1->next = token2;
    token2->prev = token1;
    token2->next = token3;
    token3->prev = token2;
    token3->next = token4;
    token4->prev = token3;
    token4->next = token5;
    token5->prev = token4;
    token5->next = token6;
    token6->prev = token5;
    token6->next = token7;
    token7->prev = token6;
    token7->next = token8;
    token8->prev = token7;
    token8->next = token9;
    token9->prev = token8;
    token9->next = token10;
    token10->prev = token9;
    token10->next = token11;
    token11->prev = token10;
    token11->next = token12;
    token12->prev = token11;
    token12->next = token13;
    token13->prev = token12;
    token13->next = token14;
    token14->prev = token13;
    token14->next = token15;
    token15->prev = token14;
    token15->next = token16;
    token16->prev = token15;

    // Call parser on the tokens
    t_token *head = token1;
    t_token *tail = token1;
    parser(&tail, &head);

    // Print the tokens after parsing
    print_list(head);

    // Free tokens
    t_token *curr = head;
    t_token *next;
    while (curr) {
        next = curr->next;
        free(curr->content);
        free(curr);
        curr = next;
    }

    return 0;
}

