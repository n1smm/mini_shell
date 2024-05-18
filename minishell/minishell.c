#include "minishell.h"

// void ft_parsing(char *input)
// {
// 	//
// }


void ft_init(t_input *commands)
{
	commands = commands;
	commands = (t_input*)safe_malloc(sizeof(t_input));

}

int main()
{
	char *input;
//	t_input *commands;

	while(1){
		input = readline("Minishell: ");
		add_history(input);
		//ft_parsing(input);
		//printf("\n");
		ft_lexer(input);
		if (ft_strncmp(input, "exit", 5) == 0)
		 	break;
		free(input);
	}
	free(input);
	return(0);
}