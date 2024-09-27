#include "libft/libft.h"
#include "minishell.h"

char	*ft_strdup2(const char *s, size_t end)
{
	char	*i;
	size_t	j;
	size_t	z;

	j = 0;
	z = 0;
	while (s[z])
	{
		z++;
	}
	i = (char *) malloc(sizeof(char) * z + 1);
	if (!i)
		return (NULL);
	while (j < (end))
	{
		i[j] = s[j];
		j++;
	}
	i[j] = '\0';
	return ((char *)i);
}

void	ft_add_token(const char *word, size_t end, t_type type, t_token **head)
{
	char	*str;

	if (!word || !head || !*head)
		return ;
	str = ft_strdup2(word, end);
	if (!str)
		return ;
	double_lstadd_back(str, head);
	(*head)->typ_token = type;
}

char	*ft_chardup(char character)
{
	char	*i;

	if (!character)
		return (NULL);
	i = (char *)safe_malloc(sizeof(char) * 2);
	i[0] = character;
	i[1] = '\0';
	return ((char *)i);
}

bool	term_character(char c)
{
	if (c == ' ' || c == '\t' || c == '|' || c == '<' \
		|| c == '>' || c == 0 || c == '\"' || c == '\'')
	{
		return (true);
	}
	else
		return (false);
}

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
	if (input[*i] == input[*i + 1])
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
		if (ft_redirect_double(input, &*i))
			return (REDIRECT_IN_DOUBLE);
		else
			return (REDIRECT_IN);
	}
	else if (input[*i] == '>')
	{
		if (ft_redirect_double(input, &*i))
			return (REDIRECT_OUT_DOUBLE);
		else
			return (REDIRECT_OUT);
	}
	else
		return (WHITESPACE);
}

static t_type	split_input_supp(char *input, size_t i, t_type type)
{
	if (input[i] == ' ')
		type = WHITESPACE;
	else if (input[i] == '|')
		type = PIPELINE;
	else if (input[i] == '<' || input[i] == '>')
		type = return_redirect_type(input, &i);
	else if (input[i] == '\"')
		type = QUOTE;
	else if (input[i] == '\'')
		type = SINGLE_QUOTE;
	return (type);
}

void	split_input(char *input, t_token **tail, t_token **head)
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
			type = split_input_supp(input, i, type);
		i++;
		ft_add_token(input + j, (i - j), type, head);
	}
	tail = tail;
}
