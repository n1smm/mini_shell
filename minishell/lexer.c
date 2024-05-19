#include "minishell.h"

static t_type ft_compare(char *cmd, int i)
{
	char *tmp;

	tmp = ft_strdup(cmd);
	tmp[i] = 0;
	if (ft_strncmp(tmp, "echo", 5) == 0)
		return (COMMAND);
	else if (ft_strncmp(tmp, "cd", 3) == 0)
		return (COMMAND);
	else if (ft_strncmp(tmp, "pwd", 4) == 0)
		return (COMMAND);
	else if (ft_strncmp(tmp, "export", 7) == 0)
		return (COMMAND);
	else if (ft_strncmp(tmp, "unset", 6) == 0)
		return (COMMAND);
	else if (ft_strncmp(tmp, "env", 4) == 0)
		return (COMMAND);
	else if (ft_strncmp(tmp, "exit", 5) == 0)
		return (COMMAND);
	else
		return (WORD);
}

static void ft_lexer(char *input)
{
	int	i;
	int	j;
	int z;
	int x;
	char *cmd;

	i = 0;
	j = 0;
	z = 0;
	cmd = NULL;
	if (input)
	{
		while ((input[i] >= 9 && input[i] <= 13) || (input[i] == 32
			&& input[i]))
			i++;
		i = 0;
		j = i;
		while (!(input[i] >= 9 && input[i] <= 13) && input[i] != 32
			&& input[i] != '|' && input[i])
			i++;
		cmd = malloc(sizeof(char) * (j + i));
		x = i - j;
		while (x > 0)
		{
			cmd[z++] = input[i];
			x--;
		}
		cmd[z] = 0;
		if ((ft_compare(input + j, i)) == WORD)
			printf("command not found: %s\n", cmd);
		else
			printf("success\n");
		free(cmd);
	}
}

void lexer_main(char *input)
{
	int i;

	i = 0;
	ft_lexer(input);
	while (input[i])
	{
		if (input[i] == '|')
			ft_lexer(input + i);
		i++;
	}
	return ;
}
