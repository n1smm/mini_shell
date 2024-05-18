#include "minishell.h"

t_cmds ft_compare(char *cmd, int i)
{
	char *tmp;

	tmp = ft_strdup(cmd);
	tmp[i] = 0;
	if (ft_strncmp(tmp, "echo", 5) == 0)
		return (ECHO);
	else if (ft_strncmp(tmp, "cd", 3) == 0)
		return (CD);
	else if (ft_strncmp(tmp, "pwd", 4) == 0)
		return (PWD);
	else if (ft_strncmp(tmp, "export", 7) == 0)
		return (EXPORT);
	else if (ft_strncmp(tmp, "unset", 6) == 0)
		return (UNSET);
	else if (ft_strncmp(tmp, "env", 4) == 0)
		return (ENV);
	else if (ft_strncmp(tmp, "exit", 5) == 0)
		return (EXIT);
	else
		return (NOT_VALID);
}

void ft_lexer(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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
		if ((ft_compare(input + j, i)) == NOT_VALID)
			printf("command not found: %s\n", input);
		else
			printf("success\n");

	}
}

void lexer_main(char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		ft_lexer(input);
		if (input[i] == '|')
			ft_lexer(input + i);
		i++;
	}
	return ;
}