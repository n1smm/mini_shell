#include "libft/libft.h"
#include "minishell.h"

void	ft_add_token(char *word, int end, t_type type, t_token **head)
{
	char *str;

	str = "hello";
	if(!word)
		return ;
	ft_strlcpy(str, word, end);
	double_lstadd_back(str, head);
	(*head)->typ_token = type;
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
		|| c == '>' || c == 0)
		return (true);
	else
	 	return (false);
}

int	ft_check_word(char *input, t_type *type)
{
	int i;
	bool	string;

	i = 0;
	string = false;
	while(input[i] && !(term_character(input[i])))
	{
		if(!(ft_isalpha(input[i])))
		{
			string = true;
		}
		i++;
	}
	if (string == true)
		*type = STRING;
	else
		*type = WORD;
	return(i - 1);
}

bool	ft_redirect_double(char *input, int *i)
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
	int i;
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
			i += ft_check_word(input, &type);
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
		else if(input[i] == '"')
			type = QUOTE;
		else if(input[i] == '\'')
			type = SINGLE_QUOTE;
		i++;
		ft_add_token(input + j, i, type, head);
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
