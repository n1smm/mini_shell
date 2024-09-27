#include "../../minishell.h"

void	check_string(t_token *curr, t_type *mod_type, int is_quote)
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