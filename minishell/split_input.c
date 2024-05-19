#include "libft/libft.h"
#include "minishell.h"

void	ft_add_token(char *word)
{
	t_token	*new;

	new = (t_token *)safe_malloc(sizeof(t_token));
	new->str = (char *)safe_malloc(ft_strlen(word) + 1);
	new->str = ft_strdup(word);
	printf("%s\n", new->str);
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
	new->str = (char *)safe_malloc(sizeof(char) * 1);
	new->str = ft_strdup(term);
	printf("%s\n", new->str);
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

void split_input(char *input)
{
	int i;
	int	j;
	int	x;
	int z;
	char *word;

	i = 0;
	j = 0;
	x = 0;
	z = 0;
	word = NULL;
	while (input[i])
	{
		while ((term_character(input[i + z++]) == false) && \
			input[i + z])
			x++;
		word = (char *)safe_malloc(sizeof(char) * x + 1);
		while ((term_character(input[i]) == false) && \
			input[i])
			word[j++] = input[i++];
		word[j] = 0;
		ft_add_token(word);
		free (word);
		j = 0;
		if (term_character(input[i]))
		{
			ft_add_token2(input[i]);
			i++;
		}
	}
}
