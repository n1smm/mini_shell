#include "libft/libft.h"
#include "minishell.h"

void	ft_add_list(char *word)
{
	t_token	*new;

	new = (t_token *)safe_malloc(sizeof(t_token));
	if(!new)
	{
		perror("Failed");
		return ;
	}
	new->str = (char *)safe_malloc(ft_strlen(word) + 1);
	new->str = ft_strdup(word);
	printf("%s\n", new->str);
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
			input[i])
			x++;
		word = (char *)malloc(sizeof(char) * x + 1);
		word[x] = 0;
		while ((term_character(input[i]) == false) && \
			input[i])
			word[j++] = input[i++];
		ft_add_list(word);
		free (word);
		if (term_character(input[i]))
			i++;
	}
}
