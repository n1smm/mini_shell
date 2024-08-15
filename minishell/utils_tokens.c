/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:39:05 by tjuvan            #+#    #+#             */
/*   Updated: 2024/08/12 17:13:35 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* #include "libft/libft.h" */
#include "minishell.h"

int	is_delimiting_node(t_token *curr)
{
	if (curr->typ_token == WHITESPACE)
		return (1);
	if (curr->typ_token == PIPELINE)
		return (1);
	if (curr->typ_token == REDIRECT_IN)
		return (1);
	if (curr->typ_token == REDIRECT_OUT)
		return (1);
	if (curr->typ_token == REDIRECT_IN_DOUBLE)
		return (1);
	if (curr->typ_token == REDIRECT_OUT_DOUBLE)
		return (1);
	if (curr->typ_token == NONPRINTABLE)
		return (1);
	else
		return(0);
}

int	is_quote_node(t_token *curr)
{
	if (curr->typ_token == QUOTE)
		return (1);
	if (curr->typ_token == SINGLE_QUOTE)
		return (1);
	return (0);
}

int	is_delimiting_type(t_type type)
{
	if (type == WHITESPACE)
		return (1);
	if (type == PIPELINE)
		return (1);
	if (type == REDIRECT_IN)
		return (1);
	if (type == REDIRECT_OUT)
		return (1);
	if (type == REDIRECT_IN_DOUBLE)
		return (1);
	if (type == REDIRECT_OUT_DOUBLE)
		return (1);
	else
		return(0);
}

bool is_redirect(t_token *curr)
{
	if (curr->typ_token == REDIRECT_IN)	
		return (true);
	if (curr->typ_token == REDIRECT_IN_DOUBLE)	
		return (true);
	if (curr->typ_token == REDIRECT_OUT)	
		return (true);
	if (curr->typ_token == REDIRECT_OUT_DOUBLE)	
		return (true);
	return (false);
}

bool is_file(t_token *curr)
{
	/* if (curr->typ_token == QUOTE) */
	/* 	return (true); */
	/* if (curr->typ_token == SINGLE_QUOTE) */
	/* 	return (true); */
	if (curr->typ_token == INFILE)
		return (true);
	if (curr->typ_token == OUTFILE)
		return (true);
	if (curr->typ_token == LIMITER)
		return (true);
	return (false);
}
