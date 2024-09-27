/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:49:29 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/09/27 17:55:10 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_check_word(char *input, size_t *i, t_type *type)
{
	bool	string;

	string = false;
	while (input[*i] && !(term_character(input[*i])))
	{
		if (!(ft_isalpha(input[*i])))
			string = true;
		(*i)++;
	}
	if (string == true)
		*type = STRING;
	else
		*type = WORD;
	(*i)--;
	return ;
}

bool	ft_redirect_double(char *input, size_t *i)
{
	if (input[*i] == input[(*i) + 1])
	{
		(*i)++;
		return (true);
	}
	return (false);
}

static t_type	return_redirect_type(char *input, size_t *i)
{
	if (input[*i] == '<')
	{
		if (ft_redirect_double(input, i))
			return (REDIRECT_IN_DOUBLE);
		else
			return (REDIRECT_IN);
	}
	else if (input[*i] == '>')
	{
		if (ft_redirect_double(input, i))
			return (REDIRECT_OUT_DOUBLE);
		else
			return (REDIRECT_OUT);
	}
	else
		return (WHITESPACE);
}

static t_type	split_input_supp(char *input, size_t *i, t_type type)
{
	if (input[*i] == ' ')
		type = WHITESPACE;
	else if (input[*i] == '|')
		type = PIPELINE;
	else if (input[*i] == '<' || input[*i] == '>')
		type = return_redirect_type(input, i);
	else if (input[*i] == '\"')
		type = QUOTE;
	else if (input[*i] == '\'')
		type = SINGLE_QUOTE;
	return (type);
}

void	split_input(char *input, t_token **head)
{
	size_t	i;
	int		j;
	t_type	type;

	i = 0;
	j = 0;
	type = WHITESPACE;
	if (!input)
		return ;
	while (input[i])
	{
		j = i;
		if (term_character(input[i]) == false)
			ft_check_word(input, &i, &type);
		else
			type = split_input_supp(input, &i, type);
		i++;
		ft_add_token(input + j, (i - j), type, head);
	}
}
