#include "minishell.h"

void ft_parsing(char *input)
{
	//
}

int main()
{
	char *input;

	while(1){
		input = readline("Minishell: ");
		add_history(input);
		ft_parsing(input);
		printf("\n");
		if (ft_strncmp(input, "exit", 5) == 0)
			break;
		free(input);
	}
	free(input);
	return(0);
}