#include "minishell.h"

// static t_type ft_compare(char *cmd, int i)
// {
// 	char *tmp;

// 	tmp = ft_strdup(cmd);
// 	tmp[i] = 0;
// 	if (ft_strncmp(tmp, "echo", 5) == 0)
// 		return (COMMAND);
// 	else if (ft_strncmp(tmp, "cd", 3) == 0)
// 		return (COMMAND);command not
// 		return (COMMAND);
// 	else if (ft_strncmp(tmp, "unset", 6) == 0)
// 		return (COMMAND);
// 	else if (ft_strncmp(tmp, "env", 4) == 0)
// 		return (COMMAND);
// 	else if (ft_strncmp(tmp, "exit", 5) == 0)
// 		return (COMMAND);
// 	else
// 		return (WORD);
// }

void ft_lexer(t_token *token)
{
	// int	i;
	// int	j;
	// int z;
	// int x;
	// char *cmd;

	// i = 0;
	// j = 0;
	// z = 0;
	// cmd = NULL;
	if (token)
	{
		if(ft_strncmp(token->content, " ", ft_strlen(token->content)) == 0)
			token->typ_token = WHITESPACE;
		else if(ft_strncmp(token->content, " ", ft_strlen(token->content)) == 0)
			token->typ_token = WORD;
		printf("prova: %s\n", token->content);
		printf("prova: %d\n", token->typ_token);
	// 	while ((token[i] >= 9 && token[i] <= 13) || (token[i] == 32
	// 		&& token[i]))
	// 		i++;
	// 	i = 0;
	// 	j = i;
	// 	while (!(token[i] >= (t_type *toke9 && token[i] <= 13)) && token[i] != 32
	// 		&& token[i] != '|' && token[i])
	// 		i++;
	// 	cmd = malloc(sizeof(char) * (j + i));
	// 	x = i - j;
	// 	while (x > 0)
	// 	{
	// 		cmd[z++] = token[i];
	// 		x--;
	// 	}
	// 	cmd[z] = 0;
	// 	//if ((ft_compare(input + j, i)) == COMMAND)
	// 	if (token->type == COMMAND)
	// 		printf("command not found: %s", cmd);
	// 	else
	// 		printf("success\n");
	// 	free(cmd);
	}
}

// void lexer_main(char *input)
// {
// 	int i;

// 	i = 0;
// 	ft_lexer(input, 0);
// 	while (input[i])
// 	{
// 		if (input[i] == '|')
// 			ft_lexer(input + i, 0);
// 		i++;
// 	}
// 	return ;
// }
