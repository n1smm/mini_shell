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
	char *str;

	str = NULL;
	if(!word)
		return ;
	//head = head;
	//type = type;
	//ft_strlcpy(str, word, end);
	str = ft_strdup2(word, end);
	printf("%s\n", str);
	double_lstadd_back(str, head);
	(*head)->typ_token = type;
	printf("type: %d\n", type);
	//ft_lexer(new);
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

void	ft_add_token2(char character)
{
	t_token	*new;
	char	*term;

	term = ft_chardup(character);
	new = (t_token *)safe_malloc(sizeof(t_token));
	new->content = (char *)safe_malloc(sizeof(char) * 1);
	new->content = ft_strdup(term);
	printf("%s\n", new->content);
	free(term);
}

bool term_character(char c)
{
	if (c == ' ' || c == '\t' || c == '|' || c == '<' \
		|| c == '>' || c == 0 || c == '\"' || c == '\'')
		return (true);
	else
	 	return (false);
}

void	ft_check_word(char *input, size_t *i, t_type *type)
{
	bool	string;

	string = false;
	while(input[*i] && !(term_character(input[*i])))
	{
		if(!(ft_isalpha(input[*i])))
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
	if(input[*i] == input[*i + 1])
	{
		(*i)++;
		return(true);
	}
	return(false);
}

void split_input(char *input, t_token **tail, t_token **head)
{
	size_t i;
	int	j;
	// int	x;
	// int z;
	//char *word;
	//t_token	*token;

	//int		len;

	i = 0;
	j = 0;

	//word = NULL;
	t_type  type = WHITESPACE;
	while (input[i])
	{
		j = i;
		if(term_character(input[i]) == false)
		{
			ft_check_word(input, &i, &type);
		}
		else if(input[i] == ' ')
			type = WHITESPACE;
		else if(input[i] == '|')
			type = PIPELINE;
		else if(input[i] == '<')
		{
			if(ft_redirect_double(input, &i))
				type = REDIRECT_IN_DOUBLE;
			else
				type = REDIRECT_IN;
		}
		else if(input[i] == '>')
		{
			if(ft_redirect_double(input, &i))
				type = REDIRECT_OUT_DOUBLE;
			else
				type = REDIRECT_OUT;
		}
		else if(input[i] == '\"')
			type = QUOTE;
		else if(input[i] == '\'')
			type = SINGLE_QUOTE;
		i++;
		ft_add_token(input + j, (i - j), type, head);
	}
	tail = tail;
	//print_list(*tail);
}
		//else if (input[i] == ' ')
		//token is whitepace
		//else if (input[i] == '|')
		//pipe
		
		// input[i]

		//here we create the node with len of j to i
		// if(term_character(input[i]) == true)
		// {
		// 	ft_term_check(input + i);
		// 	ft_add_token(input);
		// }
		// while ((term_character(input[i + z++]) == false) && 
		// 	input[i + z])
		// 	x++;
		// word = (char *)safe_malloc(sizeof(char) * x + 1);
		// while ((term_character(input[i]) == false) && 
		// 	input[i])
		// 	word[j++] = input[i++];
		// word[j] = 0;
		// ft_add_token(word);
		// free (word);
		// j = 0;
		// if (term_character(input[i]))
		// {
		// 	ft_add_token2(input[i]);
		// 	i++;
		// }
